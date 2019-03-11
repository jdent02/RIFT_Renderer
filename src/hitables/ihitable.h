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

    virtual float pdf_value(const vec3& o, const vec3& v) const { return 0.f; }

    virtual vec3 random(const vec3& o) const { return vec3(1.f, 0.f, 0.f); }
};
