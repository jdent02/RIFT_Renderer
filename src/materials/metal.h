#ifndef METAL_H
#define METAL_H

#include "material.h"

#include "hitables/hitable.h"
#include "utility/data_types/vec3.h"
#include "utility/scatter_functions.h"


class metal
    : public material
{
public:
    explicit metal(const vec3& a, const float& fuzz);
    virtual ~metal() override = default;
    virtual bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        vec3& attenuation, 
        ray& scattered) const override;

    vec3 albedo;
    float fuzz;
};

inline metal::metal(const vec3& a, const float& fuzz)
    : albedo(a), fuzz(fuzz) {}

inline bool metal::scatter(
    const ray& r_in, 
    const hit_record& rec, 
    vec3& attenuation, 
    ray& scattered) const
{
    const vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return dot(scattered.direction(), rec.normal) > 0;
}
#endif // METAL_H
