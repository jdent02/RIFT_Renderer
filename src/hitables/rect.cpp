#include "rect.h"

#include "core/data_types/aabb.h"
#include "core/data_types/vec3.h"

bool xy_rect::hit(
    const ray& r,
    float t0,
    float t1,
    hit_record& rec) const
{
    float t = (k - r.origin().z()) / r.direction().z();
    if (t < t0 || t > t1)
    {
        return false;
    }
    float x = r.origin().x() + t * r.direction().x();
    float y = r.origin().y() + t * r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0.f, 0.f, 1.f);

    return true;
}

bool xy_rect::bounding_box(float t0, float t1, aabb& box) const
{
    box = aabb(
        vec3(x0, y0, float(k - 0.0001)),
        vec3(x1, y1, float(k + 0.0001)));
    return true;
}

xy_rect::xy_rect(
    float _x0,
    float _x1,
    float _y0,
    float _y1,
    float _k,
    material* mat)
    : mp(mat)
    , x0(_x0)
    , x1(_x1)
    , y0(_y0)
    , y1(_y1)
    , k(_k) {}


// X_Z rect
bool xz_rect::hit(
    const ray& r,
    float t0,
    float t1,
    hit_record& rec) const
{
    float t = (k - r.origin().y()) / r.direction().y();
    if (t < t0 || t > t1)
    {
        return false;
    }
    float x = r.origin().x() + t * r.direction().x();
    float z = r.origin().z() + t * r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0.f, 1.f, 0.f);

    return true;
}

bool xz_rect::bounding_box(
    float t0,
    float t1,
    aabb& box) const
{
    box = aabb(
        vec3(x0, z0, float(k - 0.0001)),
        vec3(x1, z1, float(k + 0.0001)));
    return true;
}

xz_rect::xz_rect(
    float _x0,
    float _x1,
    float _z0,
    float _z1,
    float _k,
    material* mat)
    : mp(mat)
    , x0(_x0)
    , x1(_x1)
    , z0(_z0)
    , z1(_z1)
    , k(_k) {}

bool yz_rect::hit(
    const ray& r,
    float t0,
    float t1,
    hit_record& rec) const
{
    float t = (k - r.origin().x()) / r.direction().x();
    if (t < t0 || t > t1)
    {
        return false;
    }
    float y = r.origin().y() + t * r.direction().y();
    float z = r.origin().z() + t * r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(1.f, 0.f, 0.f);

    return true;
}

bool yz_rect::bounding_box(
    float t0,
    float t1,
    aabb& box) const
{
    box = aabb(
        vec3(y0, z0, float(k - 0.0001)),
        vec3(y1, z1, float(k + 0.0001)));
    return true;
}

yz_rect::yz_rect(
    float _y0,
    float _y1,
    float _z0,
    float _z1,
    float _k,
    material* mat)
    : mp(mat)
    , y0(_y0)
    , y1(_y1)
    , z0(_z0)
    , z1(_z1)
    , k(_k) {}

bool flip_normals::hit(
    const ray& r,
    float t_min,
    float t_max,
    hit_record& rec) const
{
    if (ptr->hit(r, t_min, t_max, rec))
    {
        rec.normal = -rec.normal;
        return true;
    }
    return false;
}

bool flip_normals::bounding_box(float t0, float t1, aabb& box) const
{
    return ptr->bounding_box(t0, t1, box);
}
