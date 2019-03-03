#include "render.h"

#include "utility/data_types/vec3.h"
#include "utility/utility_functions.h"
#include "camera/camera.h"
#include "rendering/sampler.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

renderer::renderer(
    const int nx,
    const int ny,
    const int ns,
    const camera cam,
    hitable* world)
    : buffer(create_buffer()),
      nx(nx),
      ny(ny),
      ns(ns),
      inv_nx(1.f / nx),
      inv_ny(1.f / ny),
      inv_ns(1.f / ns),
      cam(cam),
      world(world) {}

void renderer::do_render() const
{
    const float total_pixels_inv = 1.f / (nx * ny);
    int rendered_pixels = 0;

    time_t rand_seed = time(nullptr);
    auto seed_1 = static_cast<uint64_t>(rand_seed);

    sampler sample_gen(XORO_128_GEN);
    sample_gen.random_generator->seed_gen(seed_1);

    std::cout << "Generating Pixels..." << std::endl;
    std::cout << "Progress:" << std::endl;

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0.f, 0.f, 0.f);
            for (int s = 0; s < ns; s++)
            {
                float u = (i + sample_gen.random_generator->next()) * inv_nx;
                float v = (j + sample_gen.random_generator->next()) * inv_ny;
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }

            col *= inv_ns;
            col = vec3(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));

            std::vector<int> temp_out;
            temp_out.push_back(int(255 * col[0]));
            temp_out.push_back(int(255 * col[1]));
            temp_out.push_back(int(255 * col[2]));

            buffer->push_back(temp_out);
            rendered_pixels++;
        }

        std::cout << std::flush << "\r" << rendered_pixels * total_pixels_inv * 100;
    }

    std::cout << std::endl;
}

void renderer::write_buffer() const
{
    std::cout << "Writing Output" << std::endl;

    // std::ofstream file;
    // file.open("../image.ppm");
    // file << "P3\n" << nx << " " << ny << "\n255" << std::endl;

    int buffer_size{nx * ny * 3};

    unsigned char* out_buffer = new unsigned char[buffer_size];

    int location{0};

    for (std::vector<int>& pixel : *buffer)
    {
        out_buffer[location++] = pixel[0];
        out_buffer[location++] = pixel[1];
        out_buffer[location++] = pixel[2];
        // file << pixel[0] << " " << pixel[1] << " " << pixel[2] << std::endl;
    }

    int success = stbi_write_jpg("../image.jpg", nx, ny, 3, out_buffer, 75);

    // file.close();
    std::cout << "Done Writing Output" << std::endl;
}
