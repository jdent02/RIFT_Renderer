#include "camera.h"

#include "core/data_types/ray.h"
#include "core/data_types/vec3.h"
#include "core/rendering/utility_functions.h"


camera::camera(
    const vec3 lookfrom,
    const vec3 lookat,
    const vec3 vup,
    const float vfov,
    const float aspect,
    const float aperture,
    const float focus_dist,
    const float t0,
    const float t1)
    : origin(lookfrom)
    , lens_radius(aperture / 2.f)
    , time0(t0)
    , time1(t1)
{
    const float theta = vfov * pi / 180.f;
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
    const vec3 offset = u * rd.x() + v * rd.y();
    const float time = time0 + rand() * inv_rand_max * (time1 - time0);
    return {origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time};
}
