#include <cmath>

#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include "hitables/ihitable.h"
#include "materials/imaterial.h"
#include "utility/data_types/ray.h"
#include "utility/data_types/aabb.h"

#include <cmath>
#include <limits>
#include <memory>
#include <vector>


class imaterial;


// global const variables
constexpr float inv_rand_max = 1.f / RAND_MAX;
constexpr float pi = 3.14159f;


inline std::unique_ptr<std::vector<std::vector<int>>> create_buffer()
{
    return std::make_unique<std::vector<std::vector<int>>>();
}

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

inline vec3 color(const ray& r, ihitable* world, int depth)
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

inline aabb surrounding_box(aabb box0, aabb box1)
{
    vec3 small(
        std::fmin(box0.min().x(), box1.min().x()),
        std::fmin(box0.min().y(), box1.min().y()),
        std::fmin(box0.min().z(), box1.min().z()));

    vec3 big(
        std::fmin(box0.max().x(), box1.max().x()),
        std::fmin(box0.max().y(), box1.max().y()),
        std::fmin(box0.max().z(), box1.max().z()));
    return aabb(small, big);
}

inline int box_x_compare(
    const void* a,
    const void* b)
{
    aabb box_left, box_right;
    ihitable* ah = *(ihitable**)a;
    ihitable* bh = *(ihitable**)b;
    if (!ah->bounding_box(0.f, 0.f, box_left) || !bh->bounding_box(0.f, 0.f, box_right))
    {
        std::cerr << "No bounding box in bvh_constructor" << std::endl;
    }
    if (box_left.min().x() - box_right.min().x() < 0.f)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

inline int box_y_compare(
    const void* a,
    const void* b)
{
    aabb box_left, box_right;
    ihitable* ah = *(ihitable**)a;
    ihitable* bh = *(ihitable**)b;
    if (!ah->bounding_box(0.f, 0.f, box_left) || !bh->bounding_box(0.f, 0.f, box_right))
    {
        std::cerr << "No bounding box in bvh_constructor" << std::endl;
    }
    if (box_left.min().y() - box_right.min().y() < 0.f)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

inline int box_z_compare(
    const void* a,
    const void* b)
{
    aabb box_left, box_right;
    ihitable* ah = *(ihitable**)a;
    ihitable* bh = *(ihitable**)b;
    if (!ah->bounding_box(0.f, 0.f, box_left) || !bh->bounding_box(0.f, 0.f, box_right))
    {
        std::cerr << "No bounding box in bvh_constructor" << std::endl;
    }
    if (box_left.min().z() - box_right.min().z() < 0.f)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

#endif // UTILITY_FUNCTIONS_H
