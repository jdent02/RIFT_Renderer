#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "ihitable.h"
#include "utility/data_types/aabb.h"
#include "utility/data_types/ray.h"
#include "utility/utility_functions.h"


class hitable_list
    : public ihitable
{
  public:
    hitable_list() = default;

    hitable_list(ihitable** l, int n);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const override;

    ihitable** list{};
    int list_size{};
};

inline hitable_list::hitable_list(ihitable** l, int n)
    : list(l), list_size(n)
{
}

inline bool hitable_list::hit(
    const ray& r,
    float t_min,
    float t_max,
    hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
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

bool hitable_list::bounding_box(float t0, float t1, aabb& box) const
{
    if (list_size < 1)
    {
        return false;
    }
    aabb temp_box;
    bool first_true = list[0]->bounding_box(t0, t1, temp_box);
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

#endif // HITABLE_LIST_H
