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
#include "ihitable.h"

class xy_rect final : public ihitable
{
  public:
    xy_rect() = default;

    xy_rect(
        float      _x0,
        float      _x1,
        float      _y0,
        float      _y1,
        float      _k,
        imaterial* mat);

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    bool bounding_box(float t0, float t1, aabb& box) const override;

    imaterial* mp;
    float      x0, x1, y0, y1, k;
};

class xz_rect final : public ihitable
{
  public:
    xz_rect() = default;

    xz_rect(
        float      _x0,
        float      _x1,
        float      _z0,
        float      _z1,
        float      _k,
        imaterial* mat);

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    bool bounding_box(float t0, float t1, aabb& box) const override;

    float pdf_value(const vec3& o, const vec3& v) const override;

    vec3 random(const vec3& o) const override;

    imaterial* mp;
    float      x0, x1, z0, z1, k;
};

class yz_rect final : public ihitable
{
  public:
    yz_rect() = default;

    yz_rect(
        float      _y0,
        float      _y1,
        float      _z0,
        float      _z1,
        float      _k,
        imaterial* mat);

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    bool bounding_box(float t0, float t1, aabb& box) const override;

    imaterial* mp;
    float      y0, y1, z0, z1, k;
};

class flip_normals final : public ihitable
{
  public:
    explicit flip_normals(ihitable* p)
      : ptr(p)
    {}

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    bool bounding_box(float t0, float t1, aabb& box) const override;

    ihitable* ptr;
};
