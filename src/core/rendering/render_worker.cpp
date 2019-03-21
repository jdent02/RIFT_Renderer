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

#include "camera/i_camera.h"
#include "color_functions.h"
#include "core/data_types/Ray.h"
// #include "core/lighting_integrators/direct_lighting.h"
#include "core/lighting_integrators/i_light_integrator.h"
#include "core/lighting_integrators/light_sample_path.h"
#include "core/lighting_integrators/path_tracer.h"
#include "core/samplers/rng/drand48.h"
#include "utility/containers/scene.h"
#include "utility/containers/render_settings.h"

#include <mutex>
#include "core/lighting_integrators/direct_lighting.h"

void render_worker::run_thread(
    const float           seed,
    const int             ns,
    float*                buffer,
    const Scene*          render_scene,
    const RenderSettings& settings)
{
    std::mutex mutex;

    std::unique_ptr<ILightIntegrator> light_integrator;

    if (settings.m_light_integrator == PATH_TRACING)
    {
        light_integrator = std::make_unique<PathTracer>();
    }
    else if (settings.m_light_integrator == LIGHT_SAMPLE_PATH_TRACING)
    {
        light_integrator = std::make_unique<LightSamplePath>();
    }
    else if (settings.m_light_integrator == DIRECT_LIGHTING)
    {
        light_integrator = std::make_unique<DirectLighting>();
    }


    const int buffer_size = settings.m_resolution_x * settings.m_resolution_y * 3;

    std::unique_ptr<IRandGenerator> rn_gen = std::make_unique<DRand48>();

    rn_gen->seed_gen(static_cast<uint64_t>(seed));

    std::unique_ptr<float[]> temp_buffer = std::make_unique<float[]>(
        settings.m_resolution_x * settings.m_resolution_y * 3);

    const float inv_nx = 1.f / settings.m_resolution_x;
    const float inv_ny = 1.f / settings.m_resolution_y;

    // Render loop
    int buffer_pos{0};

    for (int j = settings.m_resolution_y - 1; j >= 0; j--)
    {
        for (int i = 0; i < settings.m_resolution_x; i++)
        {
            Vec3 col(0.f, 0.f, 0.f);
            for (int s = 0; s < ns; s++)
            {

                const float u = (i + rn_gen->get_1_d()) * inv_nx;
                const float v = (j + rn_gen->get_1_d()) * inv_ny;

                Ray r = render_scene->m_cam->get_ray(u, v);
                col += de_nan(light_integrator->trace(
                    r,
                    render_scene->m_world,
                    render_scene->m_light_source,
                    0));
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
