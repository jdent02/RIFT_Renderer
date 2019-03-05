#pragma once

#include "core/bases/texture.h"
#include "core/data_types/vec3.h"

class sky_gradient
    : public texture
{
  public:
    explicit sky_gradient() = default;

    virtual vec3 value(
        float u,
        float v,
        const vec3& p) const override;
};

