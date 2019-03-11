#pragma once

#include "hitables/ihitable.h"
#include "aabb.h"
#include "core/data_types/hit_record.h"

class bvh_node : public ihitable
{
  public:
    bvh_node() {}

    bvh_node(ihitable** l, int n, float time0, float time1);

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    bool bounding_box(float t0, float t1, aabb& box) const override;

    ihitable* left{};
    ihitable* right{};
    aabb      box;
};
