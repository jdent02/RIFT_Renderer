#include <cmath>

#include "camera.h"

#include "utility/data_types/ray.h"
#include "utility/utility_functions.h"
#include "utility/data_types/vec3.h"
#include "utility/rng/xoroshiro128.h"

camera::camera(
    vec3    lookfrom,
    vec3    lookat,
    vec3    vup,
    float   vfov,
    float   aspect,
    float   aperture,
    float   focus_dist,
    float   t0,
    float   t1)
    : origin(lookfrom), lens_radius(aperture / 2.f), time0(t0), time1(t1)
{
    const float theta = vfov * pi / 180;
    const float half_height = std::tan(theta / 2.f);
    const float half_width = aspect * half_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
}

ray camera::get_ray(float s, float t) const
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();
    float time = time0 + float(rand() / RAND_MAX) * (time1 - time0);
    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
}