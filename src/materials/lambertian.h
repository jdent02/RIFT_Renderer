#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "utility/ray.h"
#include "textures/texture.h"
#include "utility/vec3.h"

vec3 random_in_unit_sphere();

class lambertian :
    public material
{
public:
    lambertian(texture* a);
    ~lambertian() = default;

    virtual bool scatter(
        const ray& r_in,
        const hit_record& rec,
        vec3& attenuation,
        ray& scattered) const override;

    texture* albedo;
};

inline lambertian::lambertian(texture* a)
    : albedo(a) {}

inline bool lambertian::scatter(
    const ray& r_in, 
    const hit_record& rec, 
    vec3& attenuation, 
    ray& scattered) const
{
    const vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target - rec.p);
    attenuation = albedo->value(0.f, 0.f, rec.p);
    return true;
}

#endif // LAMBERTIAN_H
