#pragma once

#include "core/bases/itexture.h"
#include "core/data_types/vec3.h"

class constant_texture : public itexture
{
  public:
    constant_texture() = default;

    explicit constant_texture(vec3 c)
      : color(c){};

    virtual ~constant_texture() override = default;

    virtual vec3 value(float u, float v, const vec3& p) const override
    {
        return color;
    };

    vec3 color;
};
