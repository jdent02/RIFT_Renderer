#include "core/rendering/render_worker.h"

#include "camera/icamera.h"
#include "core/data_types/ray.h"
#include "core/data_types/scene.h"
#include "utility/containers/render_settings.h"
#include "utility/rng/drand48.h"
#include "utility/rng/xoroshiro128.h"
#include "utility_functions.h"
#include "color_functions.h"

#include <mutex>

void render_worker::run_thread(
    const float            seed,
    const int              ns,
    float*                 buffer,
    const scene&           render_scene,
    const render_settings& settings)
{
    std::mutex mutex;

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

                const float u = (i + rn_gen->next()) * inv_nx;
                const float v = (j + rn_gen->next()) * inv_ny;
                ray         r = render_scene.cam->get_ray(u, v);
                col += de_nan(color(r, render_scene.world, 0));
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
