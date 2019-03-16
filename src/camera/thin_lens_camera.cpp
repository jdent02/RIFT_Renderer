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

ThinLensCamera::ThinLensCamera(
    const Vec3  lookfrom,
    const Vec3  lookat,
    const Vec3  vup,
    const float vfov,
    const float aspect,
    const float aperture,
    const float focus_dist,
    const float t0,
    const float t1)
  : m_origin_(lookfrom)
  , m_lens_radius_(aperture / 2.f)
  , m_time0_(t0)
  , m_time1_(t1)
{
    const float theta = vfov * pi / 180.f;
    const float half_height = std::tan(theta / 2.f);
    const float half_width = aspect * half_height;

    m_w_ = unit_vector(lookfrom - lookat);
    m_u_ = unit_vector(cross(vup, m_w_));
    m_v_ = cross(m_w_, m_u_);
    m_lower_left_corner_ = m_origin_ - half_width * focus_dist * m_u_ -
                           half_height * focus_dist * m_v_ - focus_dist * m_w_;
    m_horizontal_ = 2 * half_width * focus_dist * m_u_;
    m_vertical_ = 2 * half_height * focus_dist * m_v_;
}

Ray ThinLensCamera::get_ray(float s, float t) const
{
    Vec3        rd = m_lens_radius_ * random_in_unit_disk();
    const Vec3  offset = m_u_ * rd.x() + m_v_ * rd.y();
    const float time = m_time0_ + rand() * inv_rand_max * (m_time1_ - m_time0_);
    return {m_origin_ + offset,
            m_lower_left_corner_ + s * m_horizontal_ + t * m_vertical_ -
                m_origin_ - offset,
            time};
}
