#pragma once

#include "hitables/hitable.h"
#include "vec3.h"
#include "materials/material.h"
#include "materials/lambertian.h"
#include "ray.h"

constexpr float inv_rand_max = 1.f / RAND_MAX;
#include <limits>
#include <memory>
#include <vector>



constexpr float pi = 3.14159f;

inline std::unique_ptr<std::vector<std::vector<int>>> create_buffer() { return std::make_unique<std::vector<std::vector<int>>>(); }

inline vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.f * vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX) - vec3(1.f, 1.f, 1.f);
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

    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
    {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if (depth < 10 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return emitted + attenuation * color(scattered, world, depth + 1);
        }

        return emitted;
    }

    vec3 unit_direction = unit_vector(r.direction());
    const float t = 0.5f * (unit_direction.y() + 1.f);
    return (1.f - t) * vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.f);
    // return vec3(0.f, 0.f, 0.f);
}


inline bool refract(
    const vec3& v,
    const vec3& n,
    float ni_over_nt,
    vec3& refracted)
{
    const vec3 uv = unit_vector(v);
    const float dt = dot(uv, n);
    const float discriminant = 1.f - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    return false;
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

inline float schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}


