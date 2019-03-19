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

#include "path_tracer.h"

#include "core/data_types/Ray.h"
#include "core/data_types/hit_record.h"
#include "core/data_types/vec3.h"
#include "hitables/i_hitable.h"
#include "materials/i_material.h"

Vec3 PathTracer::trace(
    const Ray& r,
    IHitable*  world,
    IHitable*  light_shape,
    int        depth) const
{
    HitRecord rec;
    if (world->hit(r, 0.001, FLT_MAX, rec))
    {
        Ray  scattered;
        Vec3 attenuation;
        Vec3 emitted = rec.m_mat_ptr->path_emitted(rec.m_u, rec.m_v, rec.m_p);
        if (depth < 10 &&
            rec.m_mat_ptr->path_scatter(r, rec, attenuation, scattered))
        {
            return emitted +
                   attenuation * trace(scattered, world, nullptr, depth + 1);
        }
        return emitted;
    }
    return Vec3(0.f, 0.f, 0.f);
}
