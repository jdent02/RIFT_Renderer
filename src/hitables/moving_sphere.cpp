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

#include "moving_sphere.h"

#include "core/acceleration_structures/aabb.h"

MovingSphere::MovingSphere(
    Vec3       cen0,
    Vec3       cen1,
    float      t0,
    float      t1,
    float      r,
    IMaterial* m)
  : m_center0(cen0)
  , m_center1(cen1)
  , m_time0(t0)
  , m_time1(t1)
  , m_radius(r)
  , m_mat_ptr(m)
{}

Vec3 MovingSphere::center(float time) const
{
    return m_center0 + ((time - m_time0) / (m_time1 - m_time0)) * (m_center1 - m_center0);
}

bool MovingSphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec)
    const
{
    const Vec3  oc = r.origin() - center(r.time());
    const float a = dot(r.direction(), r.direction());
    const float b = dot(oc, r.direction());
    const float c = dot(oc, oc) - m_radius * m_radius;
    const float discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.m_t = temp;
            rec.m_p = r.point_at_parameter(rec.m_t);
            rec.m_normal = (rec.m_p - center(r.time())) / m_radius;
            rec.m_mat_ptr = m_mat_ptr;
            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.m_t = temp;
            rec.m_p = r.point_at_parameter(rec.m_t);
            rec.m_normal = (rec.m_p - center(r.time())) / m_radius;
            rec.m_mat_ptr = m_mat_ptr;
            return true;
        }
    }

    return false;
}

bool MovingSphere::bounding_box(float t0, float t1, AABB& box) const
{
    AABB box_1{m_center0 - Vec3(m_radius, m_radius, m_radius),
               m_center0 + Vec3(m_radius, m_radius, m_radius)};
    AABB box_2{m_center1 - Vec3(m_radius, m_radius, m_radius),
               m_center1 + Vec3(m_radius, m_radius, m_radius)};
    box = surrounding_box(box_1, box_2);
    return true;
}
