// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "sphere.h"

#include "core/acceleration_structures/aabb.h"
#include "core/onb/onb.h"

#include <cfloat>

bool Sphere::hit(
    const Ray&  r,
    const float t_min,
    const float t_max,
    HitRecord&  rec) const
{
    const Vec3  oc = r.origin() - m_center_;
    const float a = dot(r.direction(), r.direction());
    const float b = dot(oc, r.direction());
    const float c = dot(oc, oc) - m_radius_ * m_radius_;
    const float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.m_t = temp;
            rec.m_p = r.point_at_parameter(rec.m_t);
            rec.m_normal = (rec.m_p - m_center_) / m_radius_;
            rec.m_mat_ptr = m_material_;
            get_sphere_uv((rec.m_p - m_center_) / m_radius_, rec.m_u, rec.m_v);
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.m_t = temp;
            rec.m_p = r.point_at_parameter(rec.m_t);
            rec.m_normal = (rec.m_p - m_center_) / m_radius_;
            rec.m_mat_ptr = m_material_;
            get_sphere_uv((rec.m_p - m_center_) / m_radius_, rec.m_u, rec.m_v);
            return true;
        }
    }

    return false;
}

bool Sphere::bounding_box(float t0, float t1, AABB& box) const
{
    box = AABB(
        m_center_ - Vec3(m_radius_, m_radius_, m_radius_),
        m_center_ + Vec3(m_radius_, m_radius_, m_radius_));
    return true;
}

float Sphere::pdf_value(const Vec3& o, const Vec3& v) const
{
    HitRecord rec;
    if (this->hit(Ray(o, v), 0.001, FLT_MAX, rec))
    {
        float cos_theta_max =
            std::sqrt(1 - m_radius_ * m_radius_ / (m_center_ - o).squared_length());
        float solid_angle = 2 * pi * (1 - cos_theta_max);
        return 1 / solid_angle;
    }
    return 0;
}

Vec3 Sphere::random(const Vec3& o) const
{
    Vec3  direction = m_center_ - o;
    float distance_squared = direction.squared_length();
    ONB   uvw;
    uvw.build_from_w(direction);
    return uvw.local(random_to_sphere(m_radius_, distance_squared));
}
