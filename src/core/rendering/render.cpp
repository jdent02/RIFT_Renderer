#include "core/rendering/render.h"

#include "utility/rng/igenerator.h"
#include "utility/data_types/vec3.h"
#include "utility/utility_functions.h"
#include "camera/camera.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "stb_image_write.h"
#include "render_unit.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

renderer::renderer(
    const int   nx,
    const int   ny,
    const int   ns,
    camera*     cam,
    hitable*    world)
  : nx(nx)
  , ny(ny)
  , ns(ns)
  , inv_nx(1.f / nx)
  , inv_ny(1.f / ny)
  , inv_ns(1.f / ns)
  , cam(cam)
  , world(world)
{
    buffer = new float[nx * ny * 3];
}

void renderer::do_render() const
{
    time_t rand_seed = time(nullptr);
    auto seed_1 = static_cast<uint64_t>(rand_seed);

    std::unique_ptr<igenerator> random_generator = std::make_unique<xoro_128>();
    random_generator->seed_gen(seed_1);

    std::cout << "Generating Pixels..." << std::endl;

    std::vector<std::thread> threads;

    int samples_per_thread = ns / 8;

    threads.reserve(8);

    std::cout << "Number of samples per thread: " << samples_per_thread << std::endl;

    for (int i = 0; i < 8; i++)
    {
        threads.push_back(
            std::thread(
                render_unit::run_thread,
                random_generator->next(),
                nx,
                ny,
                samples_per_thread,
                buffer,
                cam,
                world));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    int buffer_size{nx * ny * 3};

    for (int i = 0; i < buffer_size; i++)
    {
        buffer[i] *= inv_ns;
    }
}

void renderer::write_JPEG() const
{
    std::cout << "Writing Output" << std::endl;

    int buffer_size{nx * ny * 3};

    auto* out_buffer = new unsigned char[buffer_size];

    for (size_t i = 0; i < buffer_size; i++)
    {
        out_buffer[i] = static_cast<unsigned char>(int(255 * std::sqrt(buffer[i])));
    }

    int success = stbi_write_jpg("../image.jpg", nx, ny, 3, out_buffer, 90);

    if (success != 0)
    {
        std::cout << "Done Writing Output" << std::endl;
    }
    else
    {
        std::cout << "Image Write Failed" << std::endl;
    }
}
