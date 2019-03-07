#pragma once

// Forward declaration
class vec3;

class itexture
{
  public:
    virtual ~itexture() = default;

    virtual vec3 value(float u, float v, const vec3& p) const = 0;
};
