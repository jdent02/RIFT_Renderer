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

#pragma once

#include "core/data_types/hit_record.h"
#include "hitables/i_hitable.h"

class XYRect final : public IHitable
{
  public:
    XYRect() = default;

    XYRect(
        float      _x0,
        float      _x1,
        float      _y0,
        float      _y1,
        float      _k,
        IMaterial* mat);

    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec)
        const override;

    bool bounding_box(float t0, float t1, AABB& box) const override;

  private:
    IMaterial* m_mp_;
    float      m_x0_, m_x1_, m_y0_, m_y1_, m_k_;
};

class XZRect final : public IHitable
{
  public:
    XZRect() = default;

    XZRect(
        float      _x0,
        float      _x1,
        float      _z0,
        float      _z1,
        float      _k,
        IMaterial* mat);

    bool hit(const Ray& r, float t0, float t1, HitRecord& rec) const override;

    bool bounding_box(float t0, float t1, AABB& box) const override;

    float pdf_value(const Vec3& o, const Vec3& v) const override;

    Vec3 random(const Vec3& o) const override;

  private:
    IMaterial* m_mp_;
    float      m_x0_, m_x1_, m_z0_, m_z1_, m_k_;
};

class YZRect final : public IHitable
{
  public:
    YZRect() = default;

    YZRect(
        float      _y0,
        float      _y1,
        float      _z0,
        float      _z1,
        float      _k,
        IMaterial* mat);

    bool hit(const Ray& r, float t0, float t1, HitRecord& rec) const override;

    bool bounding_box(float t0, float t1, AABB& box) const override;

  private:
    IMaterial* m_mp_;
    float      m_y0_, m_y1_, m_z0_, m_z1_, m_k_;
};

class FlipNormals final : public IHitable
{
  public:
    explicit FlipNormals(IHitable* p)
      : m_ptr_(p)
    {}

    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec)
        const override;

    bool bounding_box(float t0, float t1, AABB& box) const override;

  private:
    IHitable* m_ptr_;
};
