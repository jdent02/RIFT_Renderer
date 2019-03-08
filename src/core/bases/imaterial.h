#pragma once

#include "core/data_types/hit_record.h"
#include "core/data_types/ray.h"
#include "core/data_types/vec3.h"

class imaterial
{
  public:
    virtual ~imaterial() = default;

    virtual bool scatter(
        const ray&        r_in,
        const hit_record& rec,
        vec3&             albedo,
        ray&              scattered,
        float&            pdf) const
    {
        return false;
    }

    virtual float scattering_pdf(
        const ray&        r_in,
        const hit_record& rec,
        const ray&        scattered) const
    {
        return false;
    }

    virtual vec3 emitted(float u, float v, const vec3& p) const
    {
        return vec3(0.f, 0.f, 0.f);
    }
};
