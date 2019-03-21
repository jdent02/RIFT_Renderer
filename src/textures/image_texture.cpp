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

#include "image_texture.h"

#include "utility/data_types/vec3.h"

ImageTexture::ImageTexture(unsigned char* pixels, const int a, const int b)
  : m_data_(pixels)
  , m_nx_(a)
  , m_ny_(b)
{}

Vec3 ImageTexture::value(const float u, const float v, const Vec3& p) const
{
    int i = int((u)*m_nx_);
    int j = int((1.f - v) * m_ny_ - 0.001f);
    if (i < 0)
    {
        i = 0;
    }
    if (j < 0)
    {
        j = 0;
    }
    if (i > m_nx_ - 1.f)
    {
        i = int(m_nx_ - 1.f);
    }
    if (j > m_ny_ - 1.f)
    {
        j = int(m_ny_ - 1.f);
    }
    float col_inv = 1.f / 255;
    float r = int(m_data_[3 * i + 3 * m_nx_ * j]) * col_inv;
    float g = int(m_data_[3 * i + 3 * m_nx_ * j + 1]) * col_inv;
    float b = int(m_data_[3 * i + 3 * m_nx_ * j + 2]) * col_inv;
    return Vec3(r, g, b);
}
