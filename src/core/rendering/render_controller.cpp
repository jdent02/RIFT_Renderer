// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "render_controller.h"

#include "core/image_writers/jpeg_writer.h"

#ifdef RIFT_USE_OPENEXR
#include "core/image_writers/openexr_writer.h"


#endif

#include "core/image_writers/png_writer.h"
#include "core/rendering/render_worker.h"
#include "core/samplers/rng/xoroshiro128.h"

#include <cstdio>
#include <thread>
#include <vector>

render_controller::render_controller(
    const render_settings& settings,
    scene*                 render_scene)
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
#ifdef RIFT_USE_OPENEXR
    else if (settings.output_writer == OPENEXR)
    {
        image_writer_ = std::make_unique<openexr_writer>();
    }
#endif
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
            render_scene_,
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
