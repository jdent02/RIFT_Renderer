#pragma once

#include "core/bases/itexture.h"

// Forward declaration
class vec3;

class checker_texture
    : public itexture
{
  public:
    checker_texture() = default;

    checker_texture(
        itexture* t0,
        itexture* t1)
        : odd(t1),
          even(t0) {};

    virtual ~checker_texture() override = default;

    virtual vec3 value(
        float u,
        float v,
        const vec3& p) const override;

    itexture* odd{};
    itexture* even{};
};
