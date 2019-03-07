#pragma once

#include "core/data_types/vec3.h"

class imaterial;

struct hit_record
{
    float      t{};
    float      u{};
    float      v{};
    vec3       p;
    vec3       normal;
    imaterial* mat_ptr{};
};
