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

#include "direct_lighting.h"

#include "materials/i_material.h"
#include "objects/hitables/i_hitable.h"
#include "utility/math_functions/pdfs/hitable_pdf.h"

#include <cfloat>

Vec3 DirectLighting::trace(
    const Ray& r,
    IHitable*  world,
    IHitable*  light_shape,
    const int  depth) const
{
    HitRecord hrec;
    if (world->hit(r, 0.001f, FLT_MAX, hrec))
    {
        ScatterRecord srec;
        const Vec3    emission =
            hrec.m_mat_ptr->emission(r, hrec, hrec.m_u, hrec.m_v, hrec.m_p);

        if (depth < 10 && hrec.m_mat_ptr->scatter(r, hrec, srec))
        {
            if (srec.m_is_specular)
            {
                return srec.m_attenuation *
                       trace(
                           srec.m_specular_ray, world, light_shape, depth + 1);
            }
            HitablePDF light(light_shape, hrec.m_p);
            Ray        scattered(hrec.m_p, light.generate(), r.time());
            float      pdf_weight = light.value(scattered.direction());

            return emission +
                   srec.m_attenuation *
                       hrec.m_mat_ptr->scatter_weight(r, hrec, scattered) *
                       trace(scattered, world, light_shape, depth + 1) /
                       pdf_weight;
        }
        return emission;
    }
    return Vec3(0.f, 0.f, 0.f);
}
