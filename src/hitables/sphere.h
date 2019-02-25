#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"
#include "vec3.h"

class sphere
    :public hitable
{
public:
    sphere();
    sphere(vec3 cen, float r, material* mat);
    ~sphere() = default;
    virtual bool hit(
        const ray& r, 
        float t_min, 
        float t_max, 
        hit_record& rec) const override;

    vec3 center_;
    float radius_;
    material* material_;
};

inline sphere::sphere(const vec3 cen, const float r, material* mat)
    :center_(cen), radius_(r), material_(mat)
{
}

inline bool sphere::hit(
    const ray&      r, 
    float           t_min, 
    float           t_max, 
    hit_record&     rec) const
{
    const vec3 oc = r.origin() - center_;
    const float a = dot(r.direction(), r.direction());
    const float b = dot(oc, r.direction());
    const float c = dot(oc, oc) - radius_ * radius_;
    const float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center_) / radius_;
            rec.mat_ptr = material_;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center_) / radius_;
            rec.mat_ptr = material_;
            return true;
        }
    }

    return false;
}

#endif // SPHERE_H
