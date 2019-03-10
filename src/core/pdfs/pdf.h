#pragma once

#include "core/data_types/vec3.h"

class pdf
{
  public:
    virtual ~pdf() = default;
    virtual float value(const vec3& direction) const = 0;
    virtual vec3  generate() const = 0;
};
