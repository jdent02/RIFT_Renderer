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

#include "utility/math_functions/utility_functions.h"
#include "utility/math_functions/onb.h"
#include "utility/math_functions/pdfs/pdf.h"

class CosinePDF final : public PDF
{
  public:
    explicit CosinePDF(const Vec3& w) { m_uvw_.build_from_w(w); }
    float value(const Vec3& direction) const override;
    Vec3  generate() const override;

  private:
    ONB m_uvw_;
};

inline float CosinePDF::value(const Vec3& direction) const
{
    float cosine = dot(unit_vector(direction), m_uvw_.w());
    if (cosine > 0)
    {
        return cosine * INV_PI;
    }
    return 0;
}

inline Vec3 CosinePDF::generate() const
{
    return m_uvw_.local(random_cosine_direction());
}
