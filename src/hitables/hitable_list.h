#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "ihitable.h"
#include "utility/data_types/ray.h"

class hitable_list
    : public ihitable
{
  public:
    hitable_list() = default;

    hitable_list(ihitable** l, int n);

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

    ihitable** list;
    int list_size;
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

#endif // HITABLE_LIST_H
