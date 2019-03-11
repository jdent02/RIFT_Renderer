#pragma once

#include "hitables/ihitable.h"
#include "aabb.h"

inline int box_x_compare(const void* a, const void* b)
{
    aabb      box_left, box_right;
    ihitable* ah = *(ihitable**)a;
    ihitable* bh = *(ihitable**)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
    {
        std::cerr << "no bounding box in bvh_node constructor\n";
    }

    if (box_left.min().x() - box_right.min().x() < 0.0)
    {
        return -1;
    }

    return 1;
}

inline int box_y_compare(const void* a, const void* b)
{
    aabb box_left, box_right;

    ihitable* ah = *(ihitable**)a;
    ihitable* bh = *(ihitable**)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
    {
        std::cerr << "no bounding box in bvh_node constructor\n";
    }

    if (box_left.min().y() - box_right.min().y() < 0.0)
    {
        return -1;
    }

    return 1;
}

inline int box_z_compare(const void* a, const void* b)
{
    aabb box_left, box_right;

    ihitable* ah = *(ihitable**)a;
    ihitable* bh = *(ihitable**)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
    {
        std::cerr << "no bounding box in bvh_node constructor\n";
    }

    if (box_left.min().z() - box_right.min().z() < 0.0)
    {
        return -1;
    }

    return 1;
}
