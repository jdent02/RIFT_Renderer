#include "sky_gradient.h"

#include "core/data_types/ray.h"

vec3 sky_gradient::value(
    float u,
    float v,
    const vec3& p) const
{
    ray direction(vec3(0.f, 0.f, 0.f), p, 0.f);
    vec3 unit_direction = unit_vector(direction.direction());

    const float t = 0.5f * (unit_direction.y() + 1.f);

    return (1.f - t) * vec3(horizon) + t * vec3(zenith);
}
