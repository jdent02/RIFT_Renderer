#pragma once

#include "core/data_types/hit_record.h"
#include "core/rendering/utility_functions.h"
#include "ihitable.h"

// Forward declarations
class imaterial;
class ray;
struct hit_record;

inline void get_sphere_uv(const vec3& p, float& u, float& v)
{
    float phi = std::atan2(p.z(), p.x());
    float theta = std::asin(p.y());
    u = 1.f - (phi + pi) / (2 * pi);
    v = (theta + pi / 2) / pi;
}

class sphere : public ihitable
{
  public:
    sphere() = default;

    sphere(const vec3 cen, const float r, imaterial* mat)
      : center(cen)
      , radius(r)
      , material(mat){};

    ~sphere() override = default;

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override;

    bool bounding_box(float t0, float t1, aabb& box) const override;

    float pdf_value(const vec3& o, const vec3& v) const override;

    vec3 random(const vec3& o) const override;
    // Properties
    vec3       center;
    float      radius{};
    imaterial* material{};
};
