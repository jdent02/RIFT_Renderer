#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"
#include "vec3.h"

// Forward declaration
class material;

struct hit_record
{
    float t;
    float u;
    float v;
    vec3 p;
    vec3 normal;
    material* mat_ptr;

};

class hitable
{
public:
    virtual ~hitable() = default;
    virtual bool hit(
        const ray&      r, 
        float           t_min, 
        float           t_max, 
        hit_record&     rec) const = 0;
};

#endif // HITABLE_H
