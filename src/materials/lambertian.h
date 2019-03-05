#pragma once


#include "core/bases/material.h"
#include "core/bases/texture.h"
#include "core/data_types/vec3.h"
#include "core/data_types/hit_record.h"

class lambertian
    : public material
{
public:
    explicit
    lambertian(texture* a)
        : albedo(a) {};

    ~lambertian() = default;

    virtual bool scatter(
        const ray& r_in,
        const hit_record& rec,
        vec3& attenuation,
        ray& scattered) const override;

    texture* albedo;
};
