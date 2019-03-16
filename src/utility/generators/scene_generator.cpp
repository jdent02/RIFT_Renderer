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

#include "scene_generator.h"

#include "camera/thin_lens_camera.h"
#include "core/acceleration_structures/bvh_node.h"
#include "core/samplers/rng/xoroshiro128.h"
#include "hitables/box.h"
#include "hitables/hitable_list.h"
#include "hitables/instancers.h"
#include "hitables/moving_sphere.h"
#include "hitables/rect.h"
#include "hitables/sky_sphere.h"
#include "materials/dielectric.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "textures/checker_tex.h"
#include "textures/constant_tex.h"
#include "textures/image_texture.h"
#include "textures/noise_texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "third_party/stb_image.h"
#include "utility/containers/render_settings.h"

// Class implementation
void scene_generator::make_random_scene(
    scene&                 in_scene,
    const render_settings& settings)
{
    const int n = 500;

    auto** list = new ihitable*[n + 1];

    igenerator* random_generator = new xoro_128;

    // Ground
    list[0] = new sphere(
        vec3(0.f, -1000.f, 0.f),
        1000.f,
        new lambertian(new checker_texture(
            new constant_texture(vec3(0.2f, 0.3f, 0.1f)),
            new constant_texture(vec3(0.9f, 0.9f, 0.9f)))));

    int i = 1;

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            const float choose_mat = random_generator->get_1_d();
            vec3        center(
                a + 0.9f * (random_generator->get_1_d()),
                0.2f,
                b + 0.9f * (random_generator->get_1_d()));
            if ((center - vec3(4.f, 0.2f, 0.f)).length() > 0.9f)
            {
                if (choose_mat < 0.8f)
                {
                    list[i++] = new moving_sphere(
                        center,
                        center +
                            vec3(0.f, 0.5f * random_generator->get_1_d(), 0.f),
                        0.f,
                        0.5f,
                        0.2f,
                        new lambertian(new constant_texture(vec3(
                            random_generator->get_1_d() *
                                (random_generator->get_1_d()),
                            random_generator->get_1_d() *
                                (random_generator->get_1_d()),
                            random_generator->get_1_d() *
                                (random_generator->get_1_d())))));
                }
                else if (choose_mat < 0.95f)
                {
                    list[i++] = new sphere(
                        center,
                        0.2f,
                        new metal(
                            vec3(
                                0.5f * (1 + random_generator->get_1_d()),
                                0.5f * (1 + random_generator->get_1_d()),
                                0.5f * (1 + random_generator->get_1_d())),
                            random_generator->get_1_d()));
                }
                else
                {
                    list[i++] = new sphere(center, 0.2f, new dielectric(1.5f));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0.f, 1.f, 0.f), 1.f, new dielectric(1.5f));

    list[i++] = new sphere(
        vec3(-1.f, 1.f, -2.f),
        1.f,
        new lambertian(new constant_texture(vec3(0.4f, 0.2f, 0.1f))));

    list[i++] = new sphere(
        vec3(1.f, 1.f, 2.f), 1.f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.03f));

    list[i++] = new flip_normals(new sky_sphere(
        new sky_gradient(vec3(1.f, 1.f, 1.f), vec3(0.3f, 0.6f, 1.f))));

    const vec3  lookfrom(0.f, 2.f, 8.f);
    const vec3  lookat(0.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    icamera* cam = new thin_lens_camera(
        lookfrom,
        lookat,
        vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings.resolution_x) / float(settings.resolution_y),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    delete random_generator;

    in_scene.cam = cam;
    in_scene.world = new bvh_node(list, i, 0.f, 0.5f);
    in_scene.light_source = nullptr;
}
/*
ihitable* scene_generator::two_spheres()
{
    auto** list = new ihitable*[2];
    list[0] = new sphere(
        vec3(0.f, -1000.f, 0.f),
        1000.f,
        new lambertian(new noise_texture(3.f)));

    list[1] = new sphere(
        vec3(0.f, 2.f, 0.f), 2.f, new lambertian(new noise_texture(3.f)));
    return new hitable_list(list, 2);
}

scene* scene_generator::earth_sphere(int x_dim, int y_dim)
{
    int            nx, ny, nn;
    unsigned char* tex_data = stbi_load(
        "../world.topo.bathy.200401.3x5400x2700.jpg", &nx, &ny, &nn, 0);

    ihitable* earth_sphere = new sphere(
        vec3(0.f, 1.f, 0.f),
        2.f,
        new lambertian(new image_texture(tex_data, nx, ny)));

    const vec3  lookfrom(0.f, 2.f, 8.f);
    const vec3  lookat(0.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    icamera* cam = new thin_lens_camera(
        lookfrom,
        lookat,
        vec3(0.f, 1.f, 0.f),
        40.f,
        float(x_dim) / float(y_dim),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    return new scene{cam, earth_sphere};
}

scene* scene_generator::rect_light(int nx, int ny)
{
    auto** list = new ihitable*[3];
    list[0] = new sphere(
        vec3(0.f, -1000.f, 0.f),
        1000.f,
        new lambertian(new noise_texture(4.f)));

    list[1] = new sphere(
        vec3(0.f, 2.f, 0.f), 2.f, new lambertian(new noise_texture(4.f)));

    list[2] = new xy_rect(
        3.f,
        5.f,
        1.f,
        3.f,
        -2.f,
        new diffuse_light(new constant_texture(vec3(4.f, 4.f, 4.f))));

    //    list[3] = new sphere(
    //        vec3(0.f, 7.f, 0.f),
    //        2.f,
    //        new diffuse_light(
    //            std::make_unique<constant_texture>(
    //                vec3(4.f, 4.f, 4.f))));

    const vec3  lookfrom(8.f, 2.f, 9.f);
    const vec3  lookat(1.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    icamera* cam = new thin_lens_camera(
        lookfrom,
        lookat,
        vec3(0.f, 1.f, 0.f),
        40.f,
        float(nx) / float(ny),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    return new scene{cam, new hitable_list(list, 3)};
}
*/

void scene_generator::cornell_box(
    scene&                 in_scene,
    const render_settings& settings)
{
    auto** list = new ihitable*[8];
    int    i = 0;

    imaterial* red =
        new lambertian(new constant_texture(vec3(0.65f, 0.05f, 0.05f)));
    imaterial* white =
        new lambertian(new constant_texture(vec3(0.73f, 0.73f, 0.73f)));
    imaterial* green =
        new lambertian(new constant_texture(vec3(0.12f, 0.45f, 0.15f)));
    imaterial* light =
        new diffuse_light(new constant_texture(vec3(15.f, 15.f, 15.f)));
    imaterial* aluminum = new metal(vec3(0.8f, 0.85f, 0.88f), 0.f);

    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));

    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);

    list[i++] = new flip_normals(new xz_rect(213, 343, 227, 332, 554, light));

    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));

    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);

    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    list[i++] = new translate(
        new rotate_y(new box(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
        vec3(130, 0, 65));

    list[i++] = new translate(
        new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
        vec3(265, 0, 295));

    const vec3  lookfrom(278.f, 278.f, -800.f);
    const vec3  lookat(278.f, 278.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    icamera* cam = new thin_lens_camera(
        lookfrom,
        lookat,
        vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings.resolution_x) / float(settings.resolution_y),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    in_scene.cam = cam;
    in_scene.world = new hitable_list(list, i);
    in_scene.light_source = new xz_rect(213, 343, 227, 332, 554, nullptr);
}
