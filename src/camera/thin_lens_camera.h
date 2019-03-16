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

#include "core/data_types/ray.h"
#include "core/data_types/vec3.h"
#include "icamera.h"

class thin_lens_camera : public icamera
{
  public:
    thin_lens_camera(
        vec3  lookfrom,
        vec3  lookat,
        vec3  vup,
        float vfov,
        float aspect,
        float aperture,
        float focus_dist,
        float t0,
        float t1);

    virtual ray get_ray(float s, float t) const override;

    // Properties
    vec3  origin;
    vec3  lower_left_corner;
    vec3  horizontal;
    vec3  vertical;
    vec3  u, v, w;
    float lens_radius;
    float time0, time1;
};
