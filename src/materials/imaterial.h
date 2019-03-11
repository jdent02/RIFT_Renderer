#pragma once

#include "core/data_types/hit_record.h"
#include "core/data_types/ray.h"
#include "core/data_types/scatter_record.h"
#include "core/data_types/vec3.h"

class imaterial
{
  public:
    virtual ~imaterial() = default;

    virtual bool scatter(
        const ray&        r_in,
        const hit_record& hrec,
        scatter_record&   srec) const
    {
        return false;
    }

    virtual float scattering_pdf(
        const ray&        r_in,
        const hit_record& hrec,
        const ray&        scattered) const
    {
        return false;
    }

    virtual vec3 emitted(
        const ray&        r_in,
        const hit_record& rec,
        float             u,
        float             v,
        const vec3&       p) const
    {
        return vec3(0.f, 0.f, 0.f);
    }
};
