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

#include "core/acceleration_structures/aabb.h"

#include "utility/data_types/ray.h"

bool AABB::hit(const Ray& r, float tmin, float tmax) const
{
    for (int a = 0; a < 3; a++)
    {
        const float inv_d = 1.f / r.direction()[a];

        float t0 = (m_min[a] - r.origin()[a]) * inv_d;
        float t1 = (m_max[a] - r.origin()[a]) * inv_d;
        if (inv_d < 0.f)
        {
            std::swap(t0, t1);
        }
        tmin = (t0 > tmin) ? t0 : tmin;
        tmax = (t1 < tmax) ? t1 : tmax;
        if (tmax <= tmin)
        {
            return false;
        }
    }
    return true;
}
