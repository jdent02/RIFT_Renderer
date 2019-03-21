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

#include "metal.h"

#include "utility/data_types/scatter_record.h"
#include "core/rendering/scatter_functions.h"
#include "utility/math_functions/utility_functions.h"

bool Metal::scatter(const Ray& r_in, const HitRecord& hrec, ScatterRecord& srec)
    const
{
    const Vec3 reflected =
        reflect(unit_vector(r_in.direction()), hrec.m_normal);
    srec.m_specular_ray =
        Ray(hrec.m_p, reflected + m_fuzz_ * random_in_unit_sphere());
    srec.m_attenuation = m_albedo_;
    srec.m_is_specular = true;
    srec.m_pdf_ptr = nullptr;
    return true;
}
