#pragma once

#include "imaterial.h"
#include "core/data_types/hit_record.h"

// Forward declaration
class vec3;

class dielectric : public imaterial
{
  public:
    explicit dielectric(const float ri)
      : ref_idx(ri){};

    ~dielectric() override = default;

    bool scatter(
        const ray&        r_in,
        const hit_record& rec,
        scatter_record&   srec) const override;

    float ref_idx;
};
