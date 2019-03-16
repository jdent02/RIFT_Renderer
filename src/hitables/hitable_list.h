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

#pragma once

#include "core/acceleration_structures/aabb.h"
#include "core/data_types/hit_record.h"

class hitable_list : public ihitable
{
  public:
    hitable_list() = default;

    hitable_list(ihitable** l, int n);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    virtual bool bounding_box(float t0, float t1, aabb& box) const override;

    ihitable** list;
    int        list_size;
};

inline hitable_list::hitable_list(ihitable** l, int n)
  : list(l)
  , list_size(n)
{}

inline bool hitable_list::hit(
    const ray&  r,
    float       t_min,
    float       t_max,
    hit_record& rec) const
{
    hit_record temp_rec;
    bool       hit_anything = false;
    float      closest_so_far = t_max;
    for (auto i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

inline bool hitable_list::bounding_box(float t0, float t1, aabb& box) const
{
    if (list_size < 1)
    {
        return false;
    }
    aabb       temp_box;
    const bool first_true = list[0]->bounding_box(t0, t1, temp_box);
    if (!first_true)
    {
        return false;
    }
    else
    {
        box = temp_box;
    }
    for (int i = 0; i < list_size; i++)
    {
        if (list[0]->bounding_box(t0, t1, temp_box))
        {
            box = surrounding_box(box, temp_box);
        }
        else
        {
            return false;
        }
    }
    return true;
}
