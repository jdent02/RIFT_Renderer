#pragma once

#include "ihitable.h"
#include "core/acceleration_structures/aabb.h"
#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"

class translate : public ihitable
{
  public:
    translate(ihitable* p, const vec3& displacement);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    virtual bool bounding_box(float t0, float t1, aabb& box) const override;

    ihitable* ptr;
    vec3      offset;
};

class rotate_y : public ihitable
{
  public:
    rotate_y(ihitable* p, float angle);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    virtual bool bounding_box(float t0, float t1, aabb& box) const override;

    ihitable* ptr;
    float     sin_theta;
    float     cos_theta;
    bool      hasbox;
    aabb      bbox;
};
