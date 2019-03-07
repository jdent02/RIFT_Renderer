#pragma once

#include "core/data_types/hit_record.h"
#include "materials/diffuse_light.h"
#include "sphere.h"
#include "textures/sky_gradient.h"

class sky_sphere : public sphere
{
  public:
    explicit sky_sphere(itexture* texture)
      : sphere(vec3(0.f, 0.f, 0.f), 100000.f, new diffuse_light(texture)){};

    ~sky_sphere() override = default;

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override
    {
        return sphere::hit(r, t_min, t_max, rec);
    }

    bool bounding_box(float t0, float t1, aabb& box) const override
    {
        return sphere::bounding_box(t0, t1, box);
    }
};
