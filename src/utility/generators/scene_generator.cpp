#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "scene_generator.h"

#include "hitables/box.h"
#include "hitables/bvh_node.h"
#include "hitables/hitable_list.h"
#include "hitables/sphere.h"
#include "hitables/moving_sphere.h"
#include "hitables/rect.h"
#include "materials/diffuse_light.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"
#include "rendering/sampler.h"
#include "textures/constant_tex.h"
#include "textures/checker_tex.h"
#include "textures/image_texture.h"
#include "textures/noise_texture.h"
#include "utility/utility_functions.h"
#include "utility/data_types/vec3.h"

#include <memory>

// Class implementation
hitable* scene_generator::make_random_scene()
{
    int n = 500;
    hitable** list = new hitable* [n + 1];

    sampler sampler(XORO_128_GEN);

    // Ground
    list[0] = new sphere(
        vec3(0.f, -1000.f, 0.f),
        1000.f,
        new lambertian(
            std::make_unique<checker_texture>(
                std::make_unique<constant_texture>(vec3(0.2f, 0.3f, 0.1f)),
                std::make_unique<constant_texture>(vec3(0.9f, 0.9f, 0.9f)))));

    int i = 1;

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            const float choose_mat = sampler.random_generator->next();
            vec3 center(
                a + 0.9f * (sampler.random_generator->next()),
                0.2f,
                b + 0.9f * (sampler.random_generator->next()));
            if ((center - vec3(4.f, 0.2f, 0.f)).length() > 0.9f)
            {
                if (choose_mat < 0.8f)
                {
                    list[i++] = new moving_sphere(
                        center,
                        center + vec3(0.f, 0.5f * sampler.random_generator->next(), 0.f),
                        0.f,
                        0.5f,
                        0.2f,
                        new lambertian(
                            std::make_unique<constant_texture>(
                                vec3(
                                    sampler.random_generator->next() * (sampler.random_generator->next()),
                                    sampler.random_generator->next() * (sampler.random_generator->next()),
                                    sampler.random_generator->next() * (sampler.random_generator->next())))));
                }
                else if (choose_mat < 0.95f)
                {
                    list[i++] = new sphere(
                        center,
                        0.2f,
                        new metal(
                            vec3(
                                0.5f * (1 + sampler.random_generator->next()),
                                0.5f * (1 + sampler.random_generator->next()),
                                0.5f * (1 + sampler.random_generator->next())),
                            sampler.random_generator->next()));
                }
                else
                {
                    list[i++] = new sphere(center, 0.2f, new dielectric(1.5f));
                }
            }
        }
    }

    list[i++] = new sphere(
        vec3(0.f, 1.f, 0.f),
        1.f,
        new dielectric(1.5f));

    list[i++] = new sphere(
        vec3(-1.f, 1.f, -2.f),
        1.f,
        new lambertian(
            std::make_unique<constant_texture>(
                vec3(0.4f, 0.2f, 0.1f))));

    list[i++] = new sphere(
        vec3(1.f, 1.f, 2.f),
        1.f,
        new metal(
            vec3(0.7f, 0.6f, 0.5f),
            0.03f));

    return new bvh_node(list, i, 0.f, 0.5f);
}

hitable* scene_generator::two_spheres()
{
    hitable** list = new hitable* [2];
    list[0] = new sphere(
        vec3(0.f, -1000.f, 0.f),
        1000.f,
        new lambertian(std::make_unique<noise_texture>(3.f)));

    list[1] = new sphere(
        vec3(0.f, 2.f, 0.f),
        2.f,
        new lambertian(std::make_unique<noise_texture>(3.f)));
    return new hitable_list(list, 2);
}

hitable* scene_generator::earth_sphere()
{
    int nx, ny, nn;
    unsigned char* tex_data = stbi_load(
        "../world.topo.bathy.200401.3x5400x2700.jpg",
        &nx, &ny, &nn, 0);

    return new sphere(
        vec3(0.f, 1.f, 0.f),
        2.f,
        new lambertian(
            std::make_unique<image_texture>(tex_data, nx, ny)));
}

hitable* scene_generator::rect_light()
{

    hitable** list = new hitable* [3];
    list[0] = new sphere(
        vec3(0.f, -1000.f, 0.f),
        1000.f,
        new lambertian(std::make_unique<noise_texture>(4.f)));

    list[1] = new sphere(
        vec3(0.f, 2.f, 0.f),
        2.f,
        new lambertian(std::make_unique<noise_texture>(4.f)));

    list[2] = new xy_rect(
        3.f,
        5.f,
        1.f,
        3.f,
        -2.f,
        new diffuse_light(
            std::make_unique<constant_texture>(
                vec3(4.f, 4.f, 4.f))));

//    list[3] = new sphere(
//        vec3(0.f, 7.f, 0.f),
//        2.f,
//        new diffuse_light(
//            std::make_unique<constant_texture>(
//                vec3(4.f, 4.f, 4.f))));

    return new hitable_list(list, 3);
}

hitable* scene_generator::cornell_box()
{
    hitable** list = new hitable* [8];
    int i = 0;
    material* red = new lambertian(
        std::make_unique<constant_texture>(
            vec3(0.65f, 0.05f, 0.05f)));
    material* white = new lambertian(
        std::make_unique<constant_texture>(
            vec3(0.73f, 0.73f, 0.73f)));
    material* green = new lambertian(
        std::make_unique<constant_texture>(
            vec3(0.12f, 0.45f, 0.15f)));
    material* light = new diffuse_light(
        std::make_unique<constant_texture>(
            vec3(15.f, 15.f, 15.f)));

    list[i++] = new flip_normals(
        new yz_rect(
            0,
            555,
            0,
            555,
            555,
            green));

    list[i++] = new yz_rect(
        0,
        555,
        0,
        555,
        0,
        red);

    list[i++] = new xz_rect(
        213,
        343,
        227,
        332,
        554,
        light);

    list[i++] = new flip_normals(
        new xz_rect(
            0,
            555,
            0,
            555,
            555,
            white));

    list[i++] = new xz_rect(
        0,
        555,
        0,
        555,
        0,
        white);

    list[i++] = new flip_normals(
        new xy_rect(
            0,
            555,
            0,
            555,
            555,
            white));

    list[i++] = new box(
        vec3(130, 0, 65),
        vec3(295, 165, 230),
        white);

    list[i++] = new box(
        vec3(265, 0, 295),
        vec3(430, 330, 460),
        white);

    return new hitable_list(list, i);
}
