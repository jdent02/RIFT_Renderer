#include "scene_generator.h"

#include "hitables/bvh_node.h"
#include "hitables/hitable_list.h"
#include "hitables/sphere.h"
#include "hitables/moving_sphere.h"
#include "materials/lambertian.h"
#include "utility/utility_functions.h"
#include "materials/metal.h"
#include "materials/dielectric.h"
#include "textures/constant_tex.h"
#include "textures/checker_tex.h"
#include "rendering/sampler.h"

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