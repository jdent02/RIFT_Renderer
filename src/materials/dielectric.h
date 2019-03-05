#pragma once


#include "core/bases/material.h"
#include "core/data_types/hit_record.h"

// Forward declaration
class vec3;

class dielectric
    : public material
{
public:
    explicit
    dielectric(const float ri)
        : ref_idx(ri) {};

    virtual ~dielectric() override = default;

    virtual bool scatter(
        const ray& r_in,
        const hit_record& rec,
        vec3& attenuation,
        ray& scattered) const override;

    float ref_idx;
};
