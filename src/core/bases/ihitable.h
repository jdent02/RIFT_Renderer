#pragma once

#include "core/data_types/hit_record.h"

class ray;
class aabb;
class imaterial;

class ihitable
{
  public:
    virtual ~ihitable() = default;

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const = 0;

    virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};
