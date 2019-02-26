#include <cmath>

#include <cmath>

#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

#include "materials/material.h"
#include "utility/data_types/ray.h"
#include "utility/data_types/vec3.h"

class sphere
    :public hitable
{
public:
    sphere() = default;
    sphere(vec3 cen, float r, material* mat) :center(cen), radius(r), material(mat) {};
    ~sphere() override = default;
    virtual bool hit(
        const ray& r, 
        float t_min, 
        float t_max, 
        hit_record& rec) const override;

    vec3 center;
    float radius;
    material* material;
};

inline bool sphere::hit(
    const ray&      r, 
    float           t_min, 
    float           t_max, 
    hit_record&     rec) const
{
    const vec3 oc = r.origin() - center;
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
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
    }

    return false;
}

#endif // SPHERE_H
