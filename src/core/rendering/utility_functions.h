#pragma once


#include "core/bases/hitable.h"
#include "core/bases/material.h"
#include "core/data_types/ray.h"
#include "core/data_types/hit_record.h"

#include <cfloat>
#include <cmath>


class material;


// global const variables
constexpr float inv_rand_max = 1.f / RAND_MAX;
constexpr float pi = 3.14159f;


inline vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(rand() * inv_rand_max, rand() * inv_rand_max, rand() * inv_rand_max) - vec3(1.f, 1.f, 1.f);
    }
    while (p.squared_length() >= 1.f);

    return p;
}

inline vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(rand() * inv_rand_max, rand() * inv_rand_max, 0.f) - vec3(1.f, 1.f, 0.f);
    }
    while (dot(p, p) >= 1.f);
    return p;
}

inline vec3 color(const ray& r, hitable* world, int depth)
{
    hit_record rec;

    if (world->hit(r, 0.001f, FLT_MAX, rec))
    {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if (depth < 10 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return emitted + attenuation * color(scattered, world, depth + 1);
            //            return attenuation;
        }

        return emitted;
    }

    //    vec3 unit_direction = unit_vector(r.direction());
    //    const float t = 0.5f * (unit_direction.y() + 1.f);
    //    return (1.f - t) * vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.f);
    return vec3(0.f, 0.f, 0.f);
}