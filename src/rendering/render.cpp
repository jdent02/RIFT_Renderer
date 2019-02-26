#include "render.h"

#include "utility/vec3.h"
#include "utility/utilities.h"
#include "utility/rng/xoroshiro128.h"
#include "camera/camera.h"

#include <fstream>
#include <iomanip>
#include <vector>
#include <iostream>

renderer::renderer(
    const int nx, 
    const int ny, 
    const int ns, 
    camera cam,
    hitable* world)
    :   buffer(create_buffer()), 
        nx(nx), 
        ny(ny), 
        ns(ns), 
        inv_nx(1.f / nx), 
        inv_ny(1.f / ny), 
        cam(cam),
        world(world)
{}

void renderer::do_render() const
{
    const float total_pixels_inv = 1.f / (nx * ny);
    int rendered_pixels = 0;

    std::cout << "Generating Pixels..." << std::endl;
    std::cout << "Progress:" << std::endl;

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0.f, 0.f, 0.f);
            for (int s = 0; s < ns; s++)
            {
                float u = (i + (float)rand() * inv_rand_max) * inv_nx;
                float v = (j + (float)rand() * inv_rand_max) * inv_ny;
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = vec3(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));

            std::vector<int> temp_out;
            temp_out.push_back(int(255.99 * col[0]));
            temp_out.push_back(int(255.99 * col[1]));
            temp_out.push_back(int(255.99 * col[2]));

            buffer->push_back(temp_out);
            rendered_pixels++;
        }

        std::cout << std::flush << "\r" << rendered_pixels * total_pixels_inv * 100;
    }

    std::cout << std::endl;
}

void renderer::write_buffer(std::vector<std::vector<int>> &buffer, const int& x_res, const int& y_res)
{
    std::cout << "Writing Output" << std::endl;

    std::ofstream file;
    file.open("../image.ppm");
    file << "P3\n" << nx << " " << ny << "\n255" << std::endl;

    for (std::vector<int> &pixel : *buffer)
    {
        file << pixel[0] << " " << pixel[1] << " " << pixel[2] << std::endl;
    }

    file.close();
    std::cout << "Done Writing Output" << std::endl;
}
