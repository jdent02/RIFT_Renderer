#include "sphere.h"

#include "utility/data_types/aabb.h"
#include "utility/data_types/ray.h"

bool sphere::hit(
    const ray& r,
    const float t_min,
    const float t_max,
    hit_record& rec) const
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
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            return true;
        }
    }

    return false;
}

bool sphere::bounding_box(float t0, float t1, aabb& box) const
{
    box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
    return true;
}
