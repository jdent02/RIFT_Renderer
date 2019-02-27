#ifndef HITABLE_H
#define HITABLE_H

#include "utility/data_types/vec3.h"

// Forward declarations
class imaterial;

class ray;

class vec3;

struct hit_record
{
    float t;
    float u;
    float v;
    vec3 p;
    vec3 normal;
    imaterial* mat_ptr;

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
};

#endif // HITABLE_H
