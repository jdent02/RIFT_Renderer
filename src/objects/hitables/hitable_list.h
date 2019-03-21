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
#include "objects/hitables/i_hitable.h"
#include "utility/data_types/hit_record.h"

#include <vector>

class HitableList : public IHitable
{
  public:
    HitableList() = default;

    explicit HitableList(std::vector<IHitable*>* l);

    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec)
        const override;

    bool bounding_box(float t0, float t1, AABB& box) const override;

  private:
    std::vector<IHitable*>* m_list_;
};

inline HitableList::HitableList(std::vector<IHitable*>* l)
  : m_list_(l)
{}

inline bool HitableList::hit(
    const Ray& r,
    float      t_min,
    float      t_max,
    HitRecord& rec) const
{
    HitRecord temp_rec;
    bool      hit_anything = false;
    float     closest_so_far = t_max;
    for (auto hitable : *m_list_)
    {
        if (hitable->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.m_t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

inline bool HitableList::bounding_box(float t0, float t1, AABB& box) const
{
    if (m_list_->empty())
    {
        return false;
    }
    AABB       temp_box;
    const bool first_true = m_list_->at(0)->bounding_box(t0, t1, temp_box);
    if (!first_true)
    {
        return false;
    }

    box = temp_box;

    for (auto& item : *m_list_)
    {
        if (item->bounding_box(t0, t1, temp_box))
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
