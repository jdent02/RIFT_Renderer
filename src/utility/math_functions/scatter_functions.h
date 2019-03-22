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

#include "utility/data_types/vec3.h"

inline bool refract(
    const Vec3& v,
    const Vec3& n,
    const float ni_over_nt,
    Vec3&       refracted)
{
    const Vec3  uv = unit_vector(v);
    const float dt = dot(uv, n);
    const float discriminant = 1.f - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }
    return false;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

inline float schlick(const float cosine, const float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return static_cast<float>(r0 + (1 - r0) * pow((1 - cosine), 5));
}
