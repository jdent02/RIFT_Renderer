#pragma once


#include "core/bases/material.h"
#include "utility/data_types/vec3.h"


class metal
    : public material
{
public:
    explicit
    metal(const vec3& a, const float& fuzz)
        : albedo(a)
        , fuzz(fuzz) {};

    virtual ~metal() override = default;

    virtual bool scatter(
        const ray& r_in,
        const hit_record& rec,
        vec3& attenuation,
        ray& scattered) const override;

    vec3 albedo;
    float fuzz;
};
