#pragma once


#include "material.h"
#include "textures/texture.h"
#include "utility/data_types/vec3.h"

#include <memory>

class lambertian
    : public material
{
public:
    explicit
    lambertian(std::unique_ptr<texture> a)
        : albedo(std::move(a)) {};

    ~lambertian() = default;

    virtual bool scatter(
        const ray& r_in,
        const hit_record& rec,
        vec3& attenuation,
        ray& scattered) const override;

    std::unique_ptr<texture> albedo;
};
