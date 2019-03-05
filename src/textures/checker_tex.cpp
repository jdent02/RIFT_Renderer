#include "checker_tex.h"

#include "core/data_types/vec3.h"


vec3 checker_texture::value(const float u, const float v, const vec3& p) const
{
    float sines = sin(10.f * p.x()) * sin(10.f * p.y()) * sin(10.f * p.z());
    if (sines < 0)
    {
        return odd->value(u, v, p);
    }
    return even->value(u, v, p);
}
