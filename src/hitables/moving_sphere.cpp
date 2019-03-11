#include "moving_sphere.h"

#include "core/acceleration_structures/aabb.h"

moving_sphere::moving_sphere(
    vec3       cen0,
    vec3       cen1,
    float      t0,
    float      t1,
    float      r,
    imaterial* m)
  : center0(cen0)
  , center1(cen1)
  , time0(t0)
  , time1(t1)
  , radius(r)
  , mat_ptr(m)
{}

vec3 moving_sphere::center(float time) const
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec)
    const
{
    const vec3  oc = r.origin() - center(r.time());
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

bool moving_sphere::bounding_box(float t0, float t1, aabb& box) const
{
    aabb box_1{center0 - vec3(radius, radius, radius),
               center0 + vec3(radius, radius, radius)};
    aabb box_2{center1 - vec3(radius, radius, radius),
               center1 + vec3(radius, radius, radius)};
    box = surrounding_box(box_1, box_2);
    return true;
}
