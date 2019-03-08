#include "core/rendering/render_worker.h"

#include "core/bases/icamera.h"
#include "core/bases/ihitable.h"
#include "core/data_types/ray.h"
#include "utility/rng/drand48.h"
#include "utility/rng/xoroshiro128.h"
#include "utility_functions.h"

#include <memory>
#include <mutex>
#include <vector>
#include "core/data_types/scene.h"

void render_worker::run_thread(
    int       seed,
    int       nx,
    int       ny,
    int       ns,
    float*    buffer,
    scene* render_scene)
{
    std::mutex                  mutex;
    const int                   buffer_size = nx * ny * 3;
    std::unique_ptr<igenerator> rn_gen = std::make_unique<xoro_128>();
    rn_gen->seed_gen(static_cast<uint64_t>(seed));

    auto* temp_buffer = new std::vector<float>;

    const float inv_nx = 1.f / nx;
    const float inv_ny = 1.f / ny;

    // Render loop
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0.f, 0.f, 0.f);
            for (int s = 0; s < ns; s++)
            {
                const float u = (i + rn_gen->next()) * inv_nx;
                const float v = (j + rn_gen->next()) * inv_ny;
                ray         r = render_scene->cam->get_ray(u, v);
                col += color(r, render_scene->world, 0);
            }

            temp_buffer->push_back(col[0]);
            temp_buffer->push_back(col[1]);
            temp_buffer->push_back(col[2]);
        }
    }

    std::lock_guard<std::mutex> lock_guard(mutex);

    for (int i = 0; i < buffer_size; i++)
    {
        buffer[i] += temp_buffer->at(i);
    }

    delete temp_buffer;
}
