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

#include "core/rendering/render_worker.h"

#include "camera/icamera.h"
#include "color_functions.h"
#include "core/data_types/ray.h"
#include "core/lighting_integrators/direct_lighting.h"
#include "core/lighting_integrators/ilight_integrator.h"
#include "core/lighting_integrators/light_sampling_pathtracer.h"
#include "core/lighting_integrators/pathtracer.h"
#include "core/samplers/rng/drand48.h"
#include "utility/containers/render_settings.h"
#include "utility/containers/scene.h"

#include <mutex>

void render_worker::run_thread(
    const float            seed,
    const int              ns,
    float*                 buffer,
    const scene*           render_scene,
    const render_settings& settings)
{
    std::mutex mutex;

    std::unique_ptr<ilight_integrator> light_integrator;

    if (settings.light_integrator == PATH_TRACING)
    {
        light_integrator = std::make_unique<pathtracer>();
    }
    else if (settings.light_integrator == LIGHT_SAMPLE_PATH_TRACING)
    {
        light_integrator = std::make_unique<light_sampling_pathtracer>();
    }
    else if (settings.light_integrator == DIRECT_LIGHTING)
    {
        light_integrator = std::make_unique<direct_lighting>();
    }

    const int buffer_size = settings.resolution_x * settings.resolution_y * 3;

    std::unique_ptr<igenerator> rn_gen = std::make_unique<drand_48>();

    rn_gen->seed_gen(static_cast<uint64_t>(seed));

    std::unique_ptr<float[]> temp_buffer = std::make_unique<float[]>(
        settings.resolution_x * settings.resolution_y * 3);

    const float inv_nx = 1.f / settings.resolution_x;
    const float inv_ny = 1.f / settings.resolution_y;

    // Render loop
    int buffer_pos{0};

    for (int j = settings.resolution_y - 1; j >= 0; j--)
    {
        for (int i = 0; i < settings.resolution_x; i++)
        {
            vec3 col(0.f, 0.f, 0.f);
            for (int s = 0; s < ns; s++)
            {

                const float u = (i + rn_gen->get_1_d()) * inv_nx;
                const float v = (j + rn_gen->get_1_d()) * inv_ny;

                ray r = render_scene->cam->get_ray(u, v);
                col += de_nan(light_integrator->trace(
                    r, render_scene->world.get(), render_scene->light_source, 0));
            }

            temp_buffer[buffer_pos++] = col[0];
            temp_buffer[buffer_pos++] = col[1];
            temp_buffer[buffer_pos++] = col[2];
        }
    }

    std::lock_guard<std::mutex> lock_guard(mutex);

    for (int i = 0; i < buffer_size; i++)
    {
        buffer[i] += temp_buffer[i];
    }
}
