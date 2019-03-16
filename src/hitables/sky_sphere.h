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

#include "core/data_types/hit_record.h"
#include "materials/diffuse_light.h"
#include "sphere.h"
#include "textures/sky_gradient.h"

class sky_sphere : public sphere
{
  public:
    explicit sky_sphere(itexture* texture)
      : sphere(vec3(0.f, 0.f, 0.f), 100000.f, new diffuse_light(texture)){};

    ~sky_sphere() override = default;

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec)
        const override
    {
        return sphere::hit(r, t_min, t_max, rec);
    }

    bool bounding_box(float t0, float t1, aabb& box) const override
    {
        return sphere::bounding_box(t0, t1, box);
    }
};
