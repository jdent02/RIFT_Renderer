#include "camera/camera.h"
#include "core/bases/hitable.h"
#include "core/data_types/ray.h"
#include "utility/rng/drand48.h"
#include "utility/rng/xoroshiro128.h"
#include "utility_functions.h"

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

namespace render_unit
{
    void run_thread(
        int seed,
        int nx,
        int ny,
        int ns,
        float* buffer,
        camera* cam,
        hitable* world)
    {
        std::mutex mutex;
        int buffer_size = nx * ny * 3;
        std::unique_ptr<igenerator> rn_gen = std::make_unique<xoro_128>();
        rn_gen->seed_gen(static_cast<uint64_t>(seed));

        std::unique_ptr<std::vector<float>> temp_buffer = std::make_unique<std::vector<float>>();

        temp_buffer->reserve(nx * ny * 3);

        float inv_nx = 1.f / nx;
        float inv_ny = 1.f / ny;

        // Render loop
        for (int j = ny - 1; j >= 0; j--)
        {
            for (int i = 0; i < nx; i++)
            {
                vec3 col(0.f, 0.f, 0.f);
                for (int s = 0; s < ns; s++)
                {
                    float u = (i + rn_gen->next()) * inv_nx;
                    float v = (j + rn_gen->next()) * inv_ny;
                    ray r = cam->get_ray(u, v);
                    col += color(r, world, 0);
                }

                temp_buffer->push_back(col[0]);
                temp_buffer->push_back(col[1]);
                temp_buffer->push_back(col[2]);
            }
        }

        std::lock_guard<std::mutex> lockGuard(mutex);

        for (size_t i = 0; i < buffer_size; i++)
        {
            buffer[i] += temp_buffer->at(i);
        }

    }
} // render_unit namespace
