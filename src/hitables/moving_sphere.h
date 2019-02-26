#include <cmath>

#include <cmath>

#ifndef FARTS_RENDERER_MOVING_SPHERE_H
#define FARTS_RENDERER_MOVING_SPHERE_H

#include "hitable.h"
#include "utility/data_types/vec3.h"


class moving_sphere
    : public hitable
{
  public:
    moving_sphere() = default;
    moving_sphere(
        vec3 cen0,
        vec3 cen1,
        float t0,
        float t1,
        float r,
        material* m);

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const override;

    vec3 center(float time) const;

    vec3 center0, center1;
    float time0{}, time1{};
    float radius{};
    material* mat_ptr{};
};

vec3 moving_sphere::center(float time) const
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(
    const ray& r,
    float t_min,
    float t_max,
    hit_record& rec) const
{
    const vec3 oc = r.origin() - center(r.time());
    const float a = dot(r.direction(), r.direction());
    const float b = dot(oc, r.direction());
    const float c = dot(oc, oc) - radius * radius;
    const float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

moving_sphere::moving_sphere(
    vec3 cen0,
    vec3 cen1,
    float t0,
    float t1,
    float r,
    material* m)
    : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m)
{}

#endif //FARTS_RENDERER_MOVING_SPHERE_H
