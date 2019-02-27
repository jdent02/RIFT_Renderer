#include "lambertian.h"

#include "utility/utility_functions.h"

bool lambertian::scatter(
    const ray& r_in,
    const hit_record& rec,
    vec3& attenuation,
    ray& scattered) const
{
    const vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target - rec.p, r_in.time());
    attenuation = albedo->value(0.f, 0.f, rec.p);
    return true;
}
