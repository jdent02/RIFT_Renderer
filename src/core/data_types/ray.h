#pragma once

#include "core/data_types/vec3.h"

class ray
{
  public:
    ray() = default;

    ray(
        const vec3& a, 
        const vec3& b,
        const float ti = 0.f)
      : A(a)
      , B(b)
      , _time(ti){};

    vec3 origin() const { return A; }

    vec3 direction() const { return B; }

    float time() const { return _time; }

    vec3 point_at_parameter(const float t) const { return A + t * B; }

    // properties
    vec3 A;
    vec3 B;
    float _time{};
};
