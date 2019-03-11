#pragma once

#include "core/data_types/ray.h"

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

inline vec3 random_to_sphere(const float radius, const float distance_squared)
{
    float r1 = rand() * inv_rand_max;
    float r2 = rand() * inv_rand_max;
    float z = 1 + r2 * (std::sqrt(1 - radius * radius / distance_squared) - 1);
    float phi = 2 * pi * r1;
    float x = cos(phi) * std::sqrt(1 - z * z);
    float y = sin(phi) * std::sqrt(1 - z * z);
    return vec3(x, y, z);
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
