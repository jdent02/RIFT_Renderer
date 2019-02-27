#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "imaterial.h"
#include "textures/texture.h"
#include "utility/data_types/ray.h"
#include "utility/data_types/vec3.h"

#include <memory>

class lambertian :
    public imaterial
{
  public:
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

#endif // LAMBERTIAN_H