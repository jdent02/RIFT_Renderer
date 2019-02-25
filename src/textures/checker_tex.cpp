#include "checker_tex.h"

#include "utility/vec3.h"

#include <complex>

vec3 checker_texture::value(float u, float v, const vec3 &p) const
{
    float sines = sin(10.f * p.x()) * sin(10.f * p.y()) * sin(10.f * p.z());
    if (sines < 0)
    {
        return odd->value(u, v, p);
    }
    return even->value(u, v, p);
}