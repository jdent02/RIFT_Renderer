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

class ONB
{
  public:
    ONB() = default;
    Vec3 operator[](int i) const { return m_axis_[i]; }
    Vec3 u() const { return m_axis_[0]; }
    Vec3 v() const { return m_axis_[1]; }
    Vec3 w() const { return m_axis_[2]; }

    Vec3 local(float a, float b, float c) const
    {
        return a * u() + b * v() + c * w();
    }

    Vec3 local(const Vec3& a) const
    {
        return a.x() * u() + a.y() * v() + a.z() * w();
    }

    void build_from_w(const Vec3& n);

  private:
    Vec3 m_axis_[3];
};

inline void ONB::build_from_w(const Vec3& n)
{
    m_axis_[2] = unit_vector(n);
    Vec3 a;
    if (fabs(w().x()) > 0.9f)
    {
        a = Vec3(0, 1, 0);
    }
    else
    {
        a = Vec3(1, 0, 0);
    }

    m_axis_[1] = unit_vector(cross(w(), a));
    m_axis_[0] = cross(w(), v());
}
