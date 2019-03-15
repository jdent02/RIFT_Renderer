#pragma once

class ihitable;
class ray;
class vec3;

enum lighting_integrator
{
    DIRECT_LIGHTING,
    PATH_TRACING,
    LIGHT_SAMPLE_PATH_TRACING
};

class ilight_integrator
{
  public:
    virtual ~ilight_integrator() = default;
    virtual vec3 trace(
        const ray& r,
        ihitable*  world,
        ihitable*  light_shape,
        const int  depth) const = 0;
};
