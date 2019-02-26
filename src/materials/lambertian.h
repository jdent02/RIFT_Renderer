#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "utility/data_types/ray.h"
#include "textures/texture.h"
#include "utility/data_types/vec3.h"

#include <memory>

vec3 random_in_unit_sphere();

class lambertian :
    public material
{
public:
    lambertian(std::unique_ptr<texture> a);
    ~lambertian() = default;

    virtual bool scatter(
        const ray& r_in,
        const hit_record& rec,
        vec3& attenuation,
        ray& scattered) const override;

    std::unique_ptr<texture> albedo;
};

inline lambertian::lambertian(std::unique_ptr<texture> a)
    : albedo(std::move(a)) {}

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
