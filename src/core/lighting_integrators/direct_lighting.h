#pragma once

#include "core/lighting_integrators/ilight_integrator.h"

class direct_lighting : public ilight_integrator
{
  public:
    direct_lighting() = default;
    vec3 trace(
        const ray& r,
        ihitable*  world,
        ihitable*  light_shape,
        const int  depth) const override;
};
