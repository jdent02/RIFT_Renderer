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
#include "core/data_types/hit_record.h"
#include "core/rendering/utility_functions.h"

bool BVHNode::bounding_box(float t0, float t1, AABB& b) const
{
    b = m_box_;
    return true;
}

bool BVHNode::hit(
    const Ray&  r,
    const float t_min,
    const float t_max,
    HitRecord&  rec) const
{
    if (m_box_.hit(r, t_min, t_max))
    {
        HitRecord  left_rec, right_rec;
        const bool hit_left = m_left_->hit(r, t_min, t_max, left_rec);
        const bool hit_right = m_right_->hit(r, t_min, t_max, right_rec);
        if (hit_left && hit_right)
        {
            if (left_rec.m_t < right_rec.m_t)
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

BVHNode::BVHNode(
    IHitable**  l,
    const int   n,
    const float time0,
    const float time1)
{
    const int axis = int(3 * (rand() * INV_RAND_MAX));
    if (axis == 0)
    {
        qsort(l, n, sizeof(IHitable*), box_x_compare);
    }
    else if (axis == 1)
    {
        qsort(l, n, sizeof(IHitable*), box_y_compare);
    }
    else
    {
        qsort(l, n, sizeof(IHitable*), box_z_compare);
    }

    if (n == 1)
    {
        m_left_ = m_right_ = l[0];
    }
    else if (n == 2)
    {
        m_left_ = l[0];
        m_right_ = l[1];
    }
    else
    {
        m_left_ = new BVHNode(l, n / 2, time0, time1);
        m_right_ = new BVHNode(l + n / 2, n - n / 2, time0, time1);
    }

    AABB box_left, box_right;
    if (!m_left_->bounding_box(time0, time1, box_left) ||
        !m_right_->bounding_box(time0, time1, box_right))
    {
        std::cerr << "no bounding Box in BVHNode constructor\n";
    }

    m_box_ = surrounding_box(box_left, box_right);
}
