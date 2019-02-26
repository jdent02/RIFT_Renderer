#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "hitables/hitable.h"
#include "material.h"
#include "utility/data_types/ray.h"


class dielectric
    :public material
{
public:
    explicit dielectric(float ri) : ref_idx(ri) {};
    virtual ~dielectric() override = default;
    virtual bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        vec3& attenuation, 
        ray& scattered) const override;
    float ref_idx;
};

#endif // DIELECTRIC_H
