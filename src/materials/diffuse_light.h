#pragma once

#include "core/bases/imaterial.h"
#include "core/bases/itexture.h"
#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"

class diffuse_light : public imaterial
{
  public:
    explicit diffuse_light(itexture* a)
      : emit(a){};

    ~diffuse_light() override = default;

    bool scatter(
        const ray&        r_in,
        const hit_record& rec,
        vec3&             attenuation,
        ray&              scattered,
        float&            pdf) const override
    {
        return false;
    }

    virtual vec3 emitted(float u, float v, const vec3& p) const override
    {
        return emit->value(u, v, p);
    }

    itexture* emit;
};
