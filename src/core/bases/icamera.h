#pragma once

#include "core/data_types/ray.h"

class icamera
{
public:
    virtual ~icamera() = default;

    virtual ray get_ray(float s, float t) const = 0;
};
