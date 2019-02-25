#include "generators.h"

#include "hitables/hitable_list.h"
#include "hitables/sphere.h"
#include "materials/lambertian.h"
#include "utilities.h"
#include "materials/metal.h"
#include "materials/dielectric.h"
#include "textures/constant_tex.h"
#include "textures/checker_tex.h"

// Class implementation
hitable* scene_generator::make_random_scene()
{
    int n = 500;
    hitable **list = new hitable *[n + 1];

    // Ground
    texture *checker = new checker_texture(
        new constant_texture(vec3(0.2f, 0.3f, 0.1f)),
        new constant_texture(vec3(0.9f, 0.9f, 0.9f)));

    list[0] = new sphere(
        vec3(0.f, -1000.f, 0.f),
        1000.f,
        new lambertian(checker));

    int i = 1;

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            const float choose_mat = rand() * inv_rand_max;
            vec3 center(
                a + 0.9f * (rand() * inv_rand_max),
                0.2f,
                b + 0.9f * (rand() * inv_rand_max));
            if ((center - vec3(4, 0.2, 0.f)).length() > 0.9f)
            {
                if (choose_mat < 0.8f)
                {
                    list[i++] = new sphere(
                        center,
                        0.2f,
                        new lambertian(new constant_texture(
                            vec3(
                                rand() * inv_rand_max * (rand() * inv_rand_max),
                                rand() * inv_rand_max * (rand() * inv_rand_max),
                                rand() * inv_rand_max * (rand() * inv_rand_max)))));
                }
                else if (choose_mat < 0.95f)
                {
                    list[i++] = new sphere(
                        center,
                        0.2f,
                        new metal(
                            vec3(
                                0.5f * (1 + rand() * inv_rand_max),
                                0.5f * (1 + rand() * inv_rand_max),
                                0.5f * (1 + rand() * inv_rand_max)),
                            rand() * inv_rand_max));
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
        new lambertian(new constant_texture(
            vec3(0.4f, 0.2f, 0.1f))));

    list[i++] = new sphere(
        vec3(1.f, 1.f, 2.f),
        1.f,
        new metal(
            vec3(0.7f, 0.6f, 0.5f),
            0.03f));

    return new hitable_list(list, i);
}