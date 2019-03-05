#pragma once


#include "hitable.h"

class box
    : public hitable
{
public:
    box() = default;
    box(
        const vec3& p0,
        const vec3& p1,
        material* ptr);

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const override;

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const override;

    vec3 pmin, pmax;
    hitable* list_ptr;
};
