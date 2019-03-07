#pragma once

#include "core/data_types/ray.h"
#include "core/data_types/vec3.h"

class aabb
{
  public:
    aabb() = default;

    aabb(
        const vec3& a, 
        const vec3& b)
      : _min(a)
      , _max(b){};

    vec3 min() const { return _min; }

    vec3 max() const { return _max; }

    bool hit(
        const ray&  r, 
        float       tmin, 
        float       tmax) const;

    vec3 _min;
    vec3 _max;
};

inline aabb surrounding_box(aabb box0, aabb box1)
{
    const vec3 small(
        std::fmin(box0.min().x(), box1.min().x()),
        std::fmin(box0.min().y(), box1.min().y()),
        std::fmin(box0.min().z(), box1.min().z()));
    const vec3 big(
        std::fmax(box0.max().x(), box1.max().x()),
        std::fmax(box0.max().y(), box1.max().y()),
        std::fmax(box0.max().z(), box1.max().z()));
    return aabb(small, big);
}
