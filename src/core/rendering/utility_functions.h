#pragma once

#include "core/bases/ihitable.h"
#include "core/bases/imaterial.h"
#include "core/data_types/hit_record.h"
#include "core/data_types/ray.h"
#include "core/pdfs/cosine_pdf.h"
#include "core/pdfs/hitable_pdf.h"
#include "core/pdfs/mixture_pdf.h"
#include "hitables/rect.h"

#include <cfloat>
#include <cmath>

// global const variables
constexpr float inv_rand_max = 1.f / RAND_MAX;
constexpr float pi = 3.14159f;
constexpr float inv_pi = 1.f / 3.14159f;

inline vec3 random_cosine_direction()
{
    float r1 = rand() * inv_rand_max;
    float r2 = rand() * inv_rand_max;
    float z = std::sqrt(1 - r2);
    float phi = 2 * pi * r1;
    float x = cos(phi) * 2 * std::sqrt(r2);
    float y = sin(phi) * 2 * std::sqrt(r2);
    return vec3(x, y, z);
}

inline vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(
                      rand() * inv_rand_max,
                      rand() * inv_rand_max,
                      rand() * inv_rand_max) -
            vec3(1.f, 1.f, 1.f);
    } while (dot(p, p) >= 1.f);

    return p;
}

inline vec3 random_on_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(
                      rand() * inv_rand_max,
                      rand() * inv_rand_max,
                      rand() * inv_rand_max) -
            vec3(1.f, 1.f, 1.f);
    } while (dot(p, p) >= 1.f);

    return unit_vector(p);
}

inline vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(rand() * inv_rand_max, rand() * inv_rand_max, 0.f) -
            vec3(1.f, 1.f, 0.f);
    } while (dot(p, p) >= 1.f);

    return p;
}

inline vec3 color(const ray& r, ihitable* world, const int depth)
{
    hit_record rec;

    if (world->hit(r, 0.001f, FLT_MAX, rec))
    {
        ray scattered;

        const vec3 emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);

        vec3 albedo;

        float pdf_val;

        if (depth < 10 &&
            rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf_val))
        {
            xz_rect     light_shape(213, 343, 227, 332, 554, 0);
            hitable_pdf p0(&light_shape, rec.p);
            cosine_pdf  p1(rec.normal);
            mixture_pdf p(&p0, &p1);
            scattered = ray(rec.p, p.generate(), r.time());
            pdf_val = p.value(scattered.direction());

            return emitted +
                   albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered) *
                       color(scattered, world, depth + 1) / pdf_val;
        }
        return emitted;
    }
    return vec3(0.f, 0.f, 0.f);
}

inline vec3 de_nan(const vec3& c)
{
    vec3 temp = c;
    if (!(temp[0] == temp[0]))
    {
        temp[0] = 0;
    }
    if (!(temp[1] == temp[1]))
    {
        temp[1] = 0;
    }
    if (!(temp[2] == temp[2]))
    {
        temp[2] = 0;
    }

    return temp;
}
