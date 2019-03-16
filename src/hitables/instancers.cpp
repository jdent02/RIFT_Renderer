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

#include "instancers.h"

#include "core/rendering/utility_functions.h"

#include <cfloat>
#include <cmath>

translate::translate(ihitable* p, const vec3& displacement)
  : ptr(p)
  , offset(displacement)
{}

bool translate::hit(
    const ray&  r,
    const float t_min,
    const float t_max,
    hit_record& rec) const
{
    const ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (ptr->hit(moved_r, t_min, t_max, rec))
    {
        rec.p += offset;
        return true;
    }
    return false;
}

bool translate::bounding_box(const float t0, const float t1, aabb& box) const
{
    if (ptr->bounding_box(t0, t1, box))
    {
        box = aabb(box.min() + offset, box.max() + offset);
        return true;
    }
    return false;
}

rotate_y::rotate_y(ihitable* p, const float angle)
  : ptr(p)
{
    const float radians = pi / 180 * angle;
    sin_theta = std::sin(radians);
    cos_theta = std::cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);
    vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
    vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                const float x = i * bbox.max().x() + (1 - i) * bbox.min().x();
                const float y = j * bbox.max().y() + (1 - j) * bbox.min().y();
                const float z = k * bbox.max().z() + (1 - k) * bbox.min().z();
                const float newx = cos_theta * x + sin_theta * z;
                const float newz = -sin_theta * x + cos_theta * z;
                vec3        tester(newx, y, newz);
                for (int c = 0; c < 3; c++)
                {
                    if (tester[c] > max[c])
                    {
                        max[c] = tester[c];
                    }
                    if (tester[c] < min[c])
                    {
                        min[c] = tester[c];
                    }
                }
            }
        }
    }
    bbox = aabb(min, max);
}

bool rotate_y::hit(const ray& r, float t_min, float t_max, hit_record& rec)
    const
{
    vec3 origin = r.origin();
    vec3 direction = r.direction();
    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];
    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];
    const ray rotated_r(origin, direction, r.time());
    if (ptr->hit(rotated_r, t_min, t_max, rec))
    {
        vec3 p = rec.p;
        vec3 normal = rec.normal;
        p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
        p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];
        normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
        normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];
        rec.p = p;
        rec.normal = normal;
        return true;
    }
    return false;
}

bool rotate_y::bounding_box(float t0, float t1, aabb& box) const
{
    box = bbox;
    return hasbox;
}
