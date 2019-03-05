#pragma once

#include "hitable.h"

#include "utility/utility_functions.h"

// Forward declarations
class material;
class ray;
struct hit_record;

inline void get_sphere_uv(
    const vec3& p,
    float& u,
    float& v)
{
    float phi = std::atan2(p.z(), p.x());
    float theta = std::asin(p.y());
    u = 1.f - (phi + pi) / (2 * pi);
    v = (theta + pi / 2) / pi;
}


class sphere
    : public hitable
{
public:
    sphere() = default;

    sphere(const vec3 cen, const float r, material* mat)
        : center(cen)
        , radius(r)
        , material(mat) {};

    ~sphere() override = default;

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const override;

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const override;

    // Properties
    vec3 center;
    float radius;
    material* material;
};
