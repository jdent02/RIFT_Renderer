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

#include "rect.h"

#include "core/acceleration_structures/aabb.h"
#include "core/rendering/utility_functions.h"
#include "utility/data_types/hit_record.h"
#include "utility/data_types/ray.h"

#include <cfloat>
#include <cmath>

bool XYRect::hit(const Ray& r, float t0, float t1, HitRecord& rec) const
{
    float t = (m_k_ - r.origin().z()) / r.direction().z();
    if (t < t0 || t > t1)
    {
        return false;
    }
    float x = r.origin().x() + t * r.direction().x();
    float y = r.origin().y() + t * r.direction().y();
    if (x < m_x0_ || x > m_x1_ || y < m_y0_ || y > m_y1_)
    {
        return false;
    }

    rec.m_u = (x - m_x0_) / (m_x1_ - m_x0_);
    rec.m_v = (y - m_y0_) / (m_y1_ - m_y0_);
    rec.m_t = t;
    rec.m_mat_ptr = m_mp_;
    rec.m_p = r.point_at_parameter(t);
    rec.m_normal = Vec3(0.f, 0.f, 1.f);

    return true;
}

bool XYRect::bounding_box(float t0, float t1, AABB& box) const
{
    box = AABB(
        Vec3(m_x0_, m_y0_, float(m_k_ - 0.0001)),
        Vec3(m_x1_, m_y1_, float(m_k_ + 0.0001)));
    return true;
}

XYRect::XYRect(
    float      _x0,
    float      _x1,
    float      _y0,
    float      _y1,
    float      _k,
    IMaterial* mat)
  : m_mp_(mat)
  , m_x0_(_x0)
  , m_x1_(_x1)
  , m_y0_(_y0)
  , m_y1_(_y1)
  , m_k_(_k)
{}

// X_Z rect
bool XZRect::hit(const Ray& r, const float t0, const float t1, HitRecord& rec)
    const
{
    float t = (m_k_ - r.origin().y()) / r.direction().y();
    if (t < t0 || t > t1)
    {
        return false;
    }
    float x = r.origin().x() + t * r.direction().x();
    float z = r.origin().z() + t * r.direction().z();
    if (x < m_x0_ || x > m_x1_ || z < m_z0_ || z > m_z1_)
    {
        return false;
    }

    rec.m_u = (x - m_x0_) / (m_x1_ - m_x0_);
    rec.m_v = (z - m_z0_) / (m_z1_ - m_z0_);
    rec.m_t = t;
    rec.m_mat_ptr = m_mp_;
    rec.m_p = r.point_at_parameter(t);
    rec.m_normal = Vec3(0.f, 1.f, 0.f);

    return true;
}

bool XZRect::bounding_box(float t0, float t1, AABB& box) const
{
    box = AABB(
        Vec3(m_x0_, m_z0_, float(m_k_ - 0.0001)),
        Vec3(m_x1_, m_z1_, float(m_k_ + 0.0001)));
    return true;
}

float XZRect::pdf_value(const Vec3& o, const Vec3& v) const
{
    HitRecord rec;
    if (this->hit(Ray(o, v), 0.001f, FLT_MAX, rec))
    {
        float area = (m_x1_ - m_x0_) * (m_z1_ - m_z0_);
        float distance_squared = rec.m_t * rec.m_t * v.squared_length();
        float cosine = fabs(dot(v, rec.m_normal) / v.length());
        return float(distance_squared / (cosine * area));
    }
    return 0.f;
}

Vec3 XZRect::random(const Vec3& o) const
{
    Vec3 random_point = Vec3(
        m_x0_ + (rand() * INV_RAND_MAX) * (m_x1_ - m_x0_),
        m_k_,
        m_z0_ + (rand() * INV_RAND_MAX) * (m_z1_ - m_z0_));
    return random_point - o;
}

XZRect::XZRect(
    float      _x0,
    float      _x1,
    float      _z0,
    float      _z1,
    float      _k,
    IMaterial* mat)
  : m_mp_(mat)
  , m_x0_(_x0)
  , m_x1_(_x1)
  , m_z0_(_z0)
  , m_z1_(_z1)
  , m_k_(_k)
{}

bool YZRect::hit(const Ray& r, const float t0, const float t1, HitRecord& rec)
    const
{
    float t = (m_k_ - r.origin().x()) / r.direction().x();
    if (t < t0 || t > t1)
    {
        return false;
    }
    float y = r.origin().y() + t * r.direction().y();
    float z = r.origin().z() + t * r.direction().z();
    if (y < m_y0_ || y > m_y1_ || z < m_z0_ || z > m_z1_)
    {
        return false;
    }

    rec.m_u = (y - m_y0_) / (m_y1_ - m_y0_);
    rec.m_v = (z - m_z0_) / (m_z1_ - m_z0_);
    rec.m_t = t;
    rec.m_mat_ptr = m_mp_;
    rec.m_p = r.point_at_parameter(t);
    rec.m_normal = Vec3(1.f, 0.f, 0.f);

    return true;
}

bool YZRect::bounding_box(float t0, float t1, AABB& box) const
{
    box = AABB(
        Vec3(m_y0_, m_z0_, float(m_k_ - 0.0001)),
        Vec3(m_y1_, m_z1_, float(m_k_ + 0.0001)));
    return true;
}

YZRect::YZRect(
    float      _y0,
    float      _y1,
    float      _z0,
    float      _z1,
    float      _k,
    IMaterial* mat)
  : m_mp_(mat)
  , m_y0_(_y0)
  , m_y1_(_y1)
  , m_z0_(_z0)
  , m_z1_(_z1)
  , m_k_(_k)
{}

bool FlipNormals::hit(
    const Ray&  r,
    const float t_min,
    const float t_max,
    HitRecord&  rec) const
{
    if (m_ptr_->hit(r, t_min, t_max, rec))
    {
        rec.m_normal = -rec.m_normal;
        return true;
    }
    return false;
}

bool FlipNormals::bounding_box(const float t0, const float t1, AABB& box) const
{
    return m_ptr_->bounding_box(t0, t1, box);
}
