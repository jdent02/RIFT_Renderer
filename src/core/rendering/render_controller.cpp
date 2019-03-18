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
#include "core/rendering/render_worker.h"
#include "core/samplers/rng/xoroshiro128.h"
#ifdef RIFT_USE_PLUGINS
#include "core/image_writers/open_exr_writer.h"
#endif
#include "core/image_writers/i_out_writer.h"
#include "core/image_writers/png_writer.h"
#include "core/lighting_integrators/i_light_integrator.h"
#include "utility/containers/render_settings.h"

#include <cstdio>
#include <thread>
#include <vector>
#include "core/image_writers/oiio_writer.h"

RenderController::RenderController(
    const RenderSettings& settings,
    const Scene*          render_scene)
  : m_inv_ns(1.f / settings.m_samples)
  , m_render_scene(render_scene)
  , m_settings(settings)
{
    if (m_settings.m_light_integrator != PATH_TRACING &&
        m_render_scene->m_light_source == nullptr)
    {
        printf("Scene has no discreet light sources, switching integrator to "
               "path tracer\n");
        m_settings.m_light_integrator = PATH_TRACING;
    }

    if (settings.m_output_writer == PNG)
    {
        m_image_writer = std::make_unique<PngWriter>();
    }
    else if (settings.m_output_writer == JPEG)
    {
        m_image_writer = std::make_unique<JpegWriter>();
    }
#ifdef RIFT_USE_PLUGINS
    else if (settings.m_output_writer == OPENEXR)
    {
        m_image_writer = std::make_unique<OpenEXRWriter>();
    }
    else if (settings.m_output_writer == OPENIMAGEIO)
    {
        m_image_writer = std::make_unique<OIIOWriter>();
    }
#endif
}

void RenderController::do_render()
{
    printf("Starting Render.....\n");
    printf("Generating Pixels...\n");

    const auto seed_1 = static_cast<uint64_t>(time(nullptr));

    m_random_generator = std::make_unique<Xoro128>();

    m_random_generator->seed_gen(seed_1);

    m_buffer = std::make_unique<float[]>(
        m_settings.m_resolution_x * m_settings.m_resolution_y * 3);

    std::vector<std::thread> threads;

    threads.reserve(m_settings.m_threads);

    int samples_per_thread = int(m_settings.m_samples / m_settings.m_threads);

    printf("Number of samples per thread: %i\n", samples_per_thread);

    for (int i = 0; i < m_settings.m_threads; i++)
    {
        threads.emplace_back(
            render_worker::run_thread,
            m_random_generator->get_1_d(),
            samples_per_thread,
            m_buffer.get(),
            m_render_scene,
            std::ref(m_settings));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    // Normalize pixel values
    const int buffer_size =
        m_settings.m_resolution_x * m_settings.m_resolution_y * 3;

    for (int i = 0; i < buffer_size; i++)
    {
        m_buffer[i] *= m_inv_ns;
    }
}
