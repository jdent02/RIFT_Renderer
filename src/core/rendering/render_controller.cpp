#include "render_controller.h"

#include "core/image_writers/jpeg_writer.h"
#include "core/image_writers/openexr_writer.h"
#include "core/image_writers/png_writer.h"
#include "core/rendering/render_worker.h"
#include "core/samplers/rng/xoroshiro128.h"

#include <cstdio>
#include <thread>
#include <vector>

render_controller::render_controller(
    const render_settings& settings,
    scene&                 render_scene)
  : inv_ns_(1.f / settings.samples)
  , render_scene_(render_scene)
  , settings_(settings)
{
    if (settings.output_writer == PNG)
    {
        image_writer_ = std::make_unique<png_writer>();
    }
    else if (settings.output_writer == JPEG)
    {
        image_writer_ = std::make_unique<jpeg_writer>();
    }
    else if (settings.output_writer == OPENEXR)
    {
        image_writer_ = std::make_unique<openexr_writer>();
    }
}

void render_controller::do_render()
{
    printf("Generating Pixels...\n");

    const auto seed_1 = static_cast<uint64_t>(time(nullptr));

    random_generator_ = std::make_unique<xoro_128>();

    random_generator_->seed_gen(seed_1);

    buffer_ = std::make_unique<float[]>(
        settings_.resolution_x * settings_.resolution_y * 3);

    std::vector<std::thread> threads;

    threads.reserve(settings_.threads);

    int samples_per_thread = int(settings_.samples / settings_.threads);

    printf("Number of samples per thread: %i\n", samples_per_thread);

    for (int i = 0; i < settings_.threads; i++)
    {
        threads.emplace_back(
            render_worker::run_thread,
            random_generator_->get_1_d(),
            samples_per_thread,
            buffer_.get(),
            std::ref(render_scene_),
            std::ref(settings_));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    // Normalize pixel values
    const int buffer_size = settings_.resolution_x * settings_.resolution_y * 3;

    for (int i = 0; i < buffer_size; i++)
    {
        buffer_[i] *= inv_ns_;
    }
}
