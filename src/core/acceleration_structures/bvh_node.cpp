// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "bvh_node.h"

#include "core/acceleration_structures/bvh_utils.h"
#include "core/rendering/utility_functions.h"

bool bvh_node::bounding_box(float t0, float t1, aabb& b) const
{
    b = box;
    return true;
}

bool bvh_node::hit(
    const ray&  r,
    const float t_min,
    const float t_max,
    hit_record& rec) const
{
    if (box.hit(r, t_min, t_max))
    {
        hit_record left_rec, right_rec;
        const bool hit_left = left->hit(r, t_min, t_max, left_rec);
        const bool hit_right = right->hit(r, t_min, t_max, right_rec);
        if (hit_left && hit_right)
        {
            if (left_rec.t < right_rec.t)
            {
                rec = left_rec;
            }
            else
            {
                rec = right_rec;
            }
            return true;
        }
        if (hit_left)
        {
            rec = left_rec;
            return true;
        }
        if (hit_right)
        {
            rec = right_rec;
            return true;
        }

        return false;
    }

    return false;
}

bvh_node::bvh_node(
    ihitable**  l,
    const int   n,
    const float time0,
    const float time1)
{
    const int axis = int(3 * (rand() * inv_rand_max));
    if (axis == 0)
    {
        qsort(l, n, sizeof(ihitable*), box_x_compare);
    }
    else if (axis == 1)
    {
        qsort(l, n, sizeof(ihitable*), box_y_compare);
    }
    else
    {
        qsort(l, n, sizeof(ihitable*), box_z_compare);
    }

    if (n == 1)
    {
        left = right = l[0];
    }
    else if (n == 2)
    {
        left = l[0];
        right = l[1];
    }
    else
    {
        left = new bvh_node(l, n / 2, time0, time1);
        right = new bvh_node(l + n / 2, n - n / 2, time0, time1);
    }

    aabb box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) ||
        !right->bounding_box(time0, time1, box_right))
    {
        std::cerr << "no bounding box in bvh_node constructor\n";
    }

    box = surrounding_box(box_left, box_right);
}
