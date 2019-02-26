#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "utility/data_types/ray.h"
#include "utility/data_types/vec3.h"


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
        float focus_dist);

    ray get_ray(float u, float v) const;

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;
};

#endif //RAYTRACER_CAMERA_H
