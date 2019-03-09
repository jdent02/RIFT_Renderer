#include "render_controller.h"

#include "core/image_writers/jpeg_writer.h"
#include "core/image_writers/png_writer.h"
#include "core/rendering/render_worker.h"
#include "utility/rng/xoroshiro128.h"

#include <iomanip>
#include <thread>
#include <vector>

render_controller::render_controller(
    const render_settings& settings,
    scene*                 render_scene)
  : buffer_(new float[settings.resolution_x * settings.resolution_y * 3])
  , inv_ns_(1.f / settings.samples)
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
}

void render_controller::do_render()
{
    const auto seed_1 = static_cast<uint64_t>(time(nullptr));

    random_generator_ = new xoro_128;
    random_generator_->seed_gen(seed_1);

    std::cout << "Generating Pixels..." << std::endl;

    std::vector<std::thread> threads;

    int samples_per_thread = int(settings_.samples / settings_.threads);

    threads.reserve(settings_.threads);

    std::cout << "Number of samples per thread: " << samples_per_thread
              << std::endl;

    for (int i = 0; i < settings_.threads; i++)
    {
        threads.emplace_back(
            render_worker::run_thread,
            int(random_generator_->next()),
            settings_.resolution_x,
            settings_.resolution_y,
            samples_per_thread,
            buffer_,
            render_scene_);
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    const int buffer_size = settings_.resolution_x * settings_.resolution_y * 3;

    for (int i = 0; i < buffer_size; i++)
    {
        buffer_[i] *= inv_ns_;
    }
}

void render_controller::cleanup() const
{
    delete[] buffer_;
    delete random_generator_;
    delete image_writer_;

    std::cout << "Renderer Deleted" << std::endl;
}
