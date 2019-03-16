// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "thin_lens_camera.h"

#include "core/rendering/utility_functions.h"

thin_lens_camera::thin_lens_camera(
    const vec3  lookfrom,
    const vec3  lookat,
    const vec3  vup,
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
    lower_left_corner = origin - half_width * focus_dist * u -
                        half_height * focus_dist * v - focus_dist * w;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
}

ray thin_lens_camera::get_ray(float s, float t) const
{
    vec3        rd = lens_radius * random_in_unit_disk();
    const vec3  offset = u * rd.x() + v * rd.y();
    const float time = time0 + rand() * inv_rand_max * (time1 - time0);
    return {origin + offset,
            lower_left_corner + s * horizontal + t * vertical - origin - offset,
            time};
}
