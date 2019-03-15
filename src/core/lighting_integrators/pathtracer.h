#pragma once
#include "ilight_integrator.h"

class pathtracer : public ilight_integrator
{
  public:
    pathtracer() = default;
    vec3 trace(
        const ray& r,
        ihitable*  world,
        ihitable*  light_shape,
        const int  depth) const override;
};
