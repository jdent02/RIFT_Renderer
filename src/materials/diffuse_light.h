#pragma once

#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"
#include "imaterial.h"
#include "textures/itexture.h"

class diffuse_light : public imaterial
{
  public:
    explicit diffuse_light(itexture* a)
      : emit(a){};

    ~diffuse_light() override = default;

    bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec)
        const override
    {
        return false;
    }

    virtual vec3 emitted(
        const ray&        r_in,
        const hit_record& rec,
        float             u,
        float             v,
        const vec3&       p) const override
    {
        if (dot(rec.normal, r_in.direction()) < 0.0)
        {
            return emit->value(u, v, p);
        }
        return vec3(0.f, 0.f, 0.f);
    }

    itexture* emit;
};
