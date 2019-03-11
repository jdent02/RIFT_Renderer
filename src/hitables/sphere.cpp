#include "sphere.h"

#include "core/acceleration_structures/aabb.h"
#include "core/onb/onb.h"

#include <cfloat>

bool sphere::hit(
    const ray&  r,
    const float t_min,
    const float t_max,
    hit_record& rec) const
{
    const vec3  oc = r.origin() - center;
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
    box = aabb(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
    return true;
}

float sphere::pdf_value(const vec3& o, const vec3& v) const
{
    hit_record rec;
    if (this->hit(ray(o, v), 0.001, FLT_MAX, rec))
    {
        float cos_theta_max =
            std::sqrt(1 - radius * radius / (center - o).squared_length());
        float solid_angle = 2 * pi * (1 - cos_theta_max);
        return 1 / solid_angle;
    }
    return 0;
}

vec3 sphere::random(const vec3& o) const
{
    vec3  direction = center - o;
    float distance_squared = direction.squared_length();
    onb   uvw;
    uvw.build_from_w(direction);
    return uvw.local(random_to_sphere(radius, distance_squared));
}
