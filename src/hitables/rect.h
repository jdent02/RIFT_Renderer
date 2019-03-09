#pragma once

#include "core/bases/ihitable.h"
#include "core/data_types/hit_record.h"

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
