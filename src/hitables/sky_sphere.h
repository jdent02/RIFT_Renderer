#pragma once

#include "sphere.h"

#include "materials/diffuse_light.h"
#include "textures/sky_gradient.h"
#include "core/data_types/hit_record.h"

class sky_sphere
    : public sphere
{
  public:
    explicit sky_sphere(texture* texture)
    : sphere(
        vec3(0.f, 0.f, 0.f),
        100000.f,
        new diffuse_light(texture)) {};

    virtual ~sky_sphere() override = default;

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const override
    {
        return sphere::hit(r, t_min, t_max, rec);
    }

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const override
    {
        return sphere::bounding_box(t0, t1, box);
    }

};
