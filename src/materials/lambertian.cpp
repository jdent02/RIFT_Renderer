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

#include "lambertian.h"

#include "core/data_types/scatter_record.h"
#include "core/pdfs/cosine_pdf.h"
#include "core/rendering/utility_functions.h"

bool Lambertian::scatter(
    const Ray&       r_in,
    const HitRecord& hrec,
    ScatterRecord&   srec) const
{
    srec.m_is_specular = false;
    srec.m_attenuation = m_albedo_->value(hrec.m_u, hrec.m_v, hrec.m_p);
    srec.m_pdf_ptr = std::make_unique<CosinePDF>(hrec.m_normal);
    return true;
}

float Lambertian::scattering_pdf(
    const Ray&       r_in,
    const HitRecord& rec,
    const Ray&       scattered) const
{
    float cosine = dot(rec.m_normal, unit_vector(scattered.direction()));
    if (cosine < 0)
    {
        cosine = 0;
    }

    return cosine * inv_pi;
}
