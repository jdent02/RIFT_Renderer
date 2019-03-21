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

#include "instancers.h"

#include "utility/math_functions/utility_functions.h"
#include "utility/data_types/hit_record.h"
#include "utility/data_types/ray.h"

#include <cfloat>
#include <cmath>

Translate::Translate(IHitable* p, const Vec3& displacement)
  : m_ptr_(p)
  , m_offset_(displacement)
{}

bool Translate::hit(
    const Ray&  r,
    const float t_min,
    const float t_max,
    HitRecord&  rec) const
{
    const Ray moved_r(r.origin() - m_offset_, r.direction(), r.time());
    if (m_ptr_->hit(moved_r, t_min, t_max, rec))
    {
        rec.m_p += m_offset_;
        return true;
    }
    return false;
}

bool Translate::bounding_box(const float t0, const float t1, AABB& box) const
{
    if (m_ptr_->bounding_box(t0, t1, box))
    {
        box = AABB(box.min() + m_offset_, box.max() + m_offset_);
        return true;
    }
    return false;
}

RotateY::RotateY(IHitable* p, const float angle)
  : m_ptr_(p)
{
    const float radians = FLOAT_M_PI / 180 * angle;
    m_sin_theta_ = std::sin(radians);
    m_cos_theta_ = std::cos(radians);
    m_hasbox_ = m_ptr_->bounding_box(0, 1, m_bbox_);
    Vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
    Vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                const float x =
                    i * m_bbox_.max().x() + (1 - i) * m_bbox_.min().x();
                const float y =
                    j * m_bbox_.max().y() + (1 - j) * m_bbox_.min().y();
                const float z =
                    k * m_bbox_.max().z() + (1 - k) * m_bbox_.min().z();
                const float newx = m_cos_theta_ * x + m_sin_theta_ * z;
                const float newz = -m_sin_theta_ * x + m_cos_theta_ * z;
                Vec3        tester(newx, y, newz);
                for (int c = 0; c < 3; c++)
                {
                    if (tester[c] > max[c])
                    {
                        max[c] = tester[c];
                    }
                    if (tester[c] < min[c])
                    {
                        min[c] = tester[c];
                    }
                }
            }
        }
    }
    m_bbox_ = AABB(min, max);
}

bool RotateY::hit(
    const Ray&  r,
    const float t_min,
    const float t_max,
    HitRecord&  rec) const
{
    Vec3 origin = r.origin();
    Vec3 direction = r.direction();
    origin[0] = m_cos_theta_ * r.origin()[0] - m_sin_theta_ * r.origin()[2];
    origin[2] = m_sin_theta_ * r.origin()[0] + m_cos_theta_ * r.origin()[2];
    direction[0] =
        m_cos_theta_ * r.direction()[0] - m_sin_theta_ * r.direction()[2];
    direction[2] =
        m_sin_theta_ * r.direction()[0] + m_cos_theta_ * r.direction()[2];
    const Ray rotated_r(origin, direction, r.time());
    if (m_ptr_->hit(rotated_r, t_min, t_max, rec))
    {
        Vec3 p = rec.m_p;
        Vec3 normal = rec.m_normal;
        p[0] = m_cos_theta_ * rec.m_p[0] + m_sin_theta_ * rec.m_p[2];
        p[2] = -m_sin_theta_ * rec.m_p[0] + m_cos_theta_ * rec.m_p[2];
        normal[0] =
            m_cos_theta_ * rec.m_normal[0] + m_sin_theta_ * rec.m_normal[2];
        normal[2] =
            -m_sin_theta_ * rec.m_normal[0] + m_cos_theta_ * rec.m_normal[2];
        rec.m_p = p;
        rec.m_normal = normal;
        return true;
    }
    return false;
}

bool RotateY::bounding_box(float t0, float t1, AABB& box) const
{
    box = m_bbox_;
    return m_hasbox_;
}
