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

#include "pdf.h"

class MixturePDF : public PDF
{
  public:
    MixturePDF(PDF* p0, PDF* p1)
    {
        m_p_[0] = p0;
        m_p_[1] = p1;
    }

    float value(const Vec3& direction) const override
    {
        return float(
            0.5 * m_p_[0]->value(direction) + 0.5 * m_p_[1]->value(direction));
    }

    Vec3 generate() const override
    {
        if (rand() * (1.f / RAND_MAX) < 0.5)
        {
            return m_p_[0]->generate();
        }
        return m_p_[1]->generate();
    }

  private:
    PDF* m_p_[2]{};
};
