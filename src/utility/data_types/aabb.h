#ifndef FARTS_RENDERER_AABB_H
#define FARTS_RENDERER_AABB_H

#include "ray.h"
#include "vec3.h"


class aabb
{
  public:
    aabb() = default;
    aabb(const vec3& a, const vec3& b) : _min(a), _max(b) {};
    vec3 min() const { return _min; }
    vec3 max() const { return _max; }

    bool hit(const ray& r, float tmin, float tmax) const;

    // Variables
    vec3 _min;
    vec3 _max;
};


#endif //FARTS_RENDERER_AABB_H
