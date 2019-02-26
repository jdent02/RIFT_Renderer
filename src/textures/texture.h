#pragma once
#include "utility/data_types/vec3.h"

class texture
{
public:
    virtual ~texture() = default;
    virtual vec3 value(
        float u, 
        float v, 
        const vec3& p) const = 0;
};