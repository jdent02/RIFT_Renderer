#ifndef FARTS_RENDERER_BVH_NODE_H
#define FARTS_RENDERER_BVH_NODE_H


#include "ihitable.h"

class bvh_node
    :public ihitable
{
  public:
    bvh_node() = default;
    bvh_node(
        ihitable** l,
        int n,
        float time0,
        float time1);

    virtual ~bvh_node() override = default;

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const override;

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const override;

    ihitable* left;
    ihitable* right;
    aabb b_box;

};


#endif //FARTS_RENDERER_BVH_NODE_H
