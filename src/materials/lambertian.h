#pragma once

#include "core/bases/imaterial.h"
#include "core/bases/itexture.h"
#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"

class lambertian : public imaterial
{
  public:
    explicit lambertian(itexture* a)
      : albedo(a){};

    ~lambertian() = default;

    virtual bool scatter(
        const ray&        r_in,
        const hit_record& rec,
        vec3&             attenuation,
        ray&              scattered) const override;

    itexture* albedo;
};
