#pragma once

#include "core/bases/itexture.h"
#include "core/data_types/vec3.h"

class sky_gradient
    : public itexture
{
  public:
    sky_gradient(
        const vec3& horizon,
        const vec3& zenith)
        : horizon(horizon),
          zenith(zenith) {};

    virtual vec3 value(
        float u,
        float v,
        const vec3& p) const override;

    vec3 horizon;
    vec3 zenith;
};
