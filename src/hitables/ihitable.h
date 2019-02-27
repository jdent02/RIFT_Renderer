#ifndef HITABLE_H
#define HITABLE_H

#include "utility/data_types/aabb.h"
#include "utility/data_types/ray.h"
#include "utility/data_types/vec3.h"

// Forward declaration
class imaterial;

struct hit_record
{
    float t{};
    float u{};
    float v{};
    vec3 p;
    vec3 normal;
    imaterial* mat_ptr{};

};

class ihitable
{
  public:
    virtual ~ihitable() = default;

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const = 0;

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const = 0;
};

#endif // HITABLE_H
