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

#pragma once

#include "camera/i_camera.h"
#include "core/data_types/ray.h"
#include "core/data_types/vec3.h"

class ThinLensCamera : public ICamera
{
  public:
    ThinLensCamera(
        Vec3  lookfrom,
        Vec3  lookat,
        Vec3  vup,
        float vfov,
        float aspect,
        float aperture,
        float focus_dist,
        float t0,
        float t1);

    Ray get_ray(float s, float t) const override;

  private:
    Vec3  m_origin_;
    Vec3  m_lower_left_corner_;
    Vec3  m_horizontal_;
    Vec3  m_vertical_;
    Vec3  m_u_, m_v_, m_w_;
    float m_lens_radius_;
    float m_time0_, m_time1_;
};
