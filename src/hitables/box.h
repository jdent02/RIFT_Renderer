#pragma once

#include "core/bases/ihitable.h"
#include "core/data_types/hit_record.h"

class box : public ihitable
{
  public:
    box() = default;
    box(const vec3& p0, const vec3& p1, imaterial* ptr);

    ~box() override { delete list_ptr; }

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    virtual bool bounding_box(float t0, float t1, aabb& box) const override;

    vec3      pmin, pmax;
    ihitable* list_ptr;
};
