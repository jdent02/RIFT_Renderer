#pragma once


#include "core/bases/hitable.h"
#include "utility/data_types/vec3.h"

class moving_sphere
    : public hitable
{
public:
    moving_sphere() = default;

    moving_sphere(
        vec3 cen0,
        vec3 cen1,
        float t0,
        float t1,
        float r,
        material* m);

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const override;

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const override;

    vec3 center(float time) const;

    vec3 center0, center1;
    float time0{}, time1{};
    float radius{};
    material* mat_ptr{};
};
