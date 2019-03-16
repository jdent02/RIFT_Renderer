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

#include "core/data_types/vec3.h"

class onb
{
  public:
    onb() = default;
    vec3 operator[](int i) const { return axis[i]; }
    vec3 u() const { return axis[0]; }
    vec3 v() const { return axis[1]; }
    vec3 w() const { return axis[2]; }

    vec3 local(float a, float b, float c) const
    {
        return a * u() + b * v() + c * w();
    }

    vec3 local(const vec3& a) const
    {
        return a.x() * u() + a.y() * v() + a.z() * w();
    }

    void build_from_w(const vec3& n);

    vec3 axis[3];
};

inline void onb::build_from_w(const vec3& n)
{
    axis[2] = unit_vector(n);
    vec3 a;
    if (fabs(w().x()) > 0.9f)
    {
        a = vec3(0, 1, 0);
    }
    else
    {
        a = vec3(1, 0, 0);
    }

    axis[1] = unit_vector(cross(w(), a));
    axis[0] = cross(w(), v());
}
