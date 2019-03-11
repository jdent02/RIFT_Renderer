#pragma once

#include "imaterial.h"
#include "textures/itexture.h"
#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"

class lambertian : public imaterial
{
  public:
    explicit lambertian(itexture* a)
      : albedo(a){};

    ~lambertian() = default;

    bool scatter(
        const ray&        r_in,
        const hit_record& rec,
        scatter_record& srec) const override;

    float scattering_pdf(
        const ray&        r_in,
        const hit_record& rec,
        const ray&        scattered) const override;

    itexture* albedo;
};
