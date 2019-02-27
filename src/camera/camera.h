#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "utility/data_types/vec3.h"

// Forward declaration
class ray;

class camera
{
  public:
    camera(
        vec3 lookfrom,
        vec3 lookat,
        vec3 vup,
        float vfov,
        float aspect,
        float aperture,
        float focus_dist,
        float t0,
        float t1);

    ray get_ray(float s, float t) const;

    // Properties
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;
    float time0, time1;
};

#endif //RAYTRACER_CAMERA_H
