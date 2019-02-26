#include "camera.h"

#include "utility/ray.h"
#include "utility/utilities.h"
#include "utility/vec3.h"

camera::camera(
    vec3 lookfrom,
    vec3 lookat,
    vec3 vup,
    float vfov,
    float aspect,
    float aperture,
    float focus_dist)
    : origin(lookfrom), lens_radius(aperture / 2.f)
{
    const float theta = vfov * pi / 180;
    const float half_height = tan(theta / 2.f);
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
    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}