#pragma once

#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"
#include "imaterial.h"

class metal : public imaterial
{
  public:
    explicit metal(const vec3& a, const float& fuzz)
      : albedo(a)
      , fuzz(fuzz){};

    ~metal() override = default;

    bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec)
        const override;

    vec3  albedo;
    float fuzz;
};
