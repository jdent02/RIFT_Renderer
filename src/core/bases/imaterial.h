#pragma once

#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"

// Forward declarations
struct hit_record;
class ray;

class imaterial
{
  public:
    virtual ~imaterial() = default;

    virtual bool scatter(
        const ray&        r_in,
        const hit_record& rec,
        vec3&             attenuation,
        ray&              scattered) const = 0;

    virtual vec3 emitted(float u, float v, const vec3& p) const
    {
        return vec3(0.f, 0.f, 0.f);
    }
};
