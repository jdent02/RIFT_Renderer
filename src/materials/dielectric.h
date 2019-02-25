#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "hitable.h"
#include "material.h"
#include "ray.h"


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
