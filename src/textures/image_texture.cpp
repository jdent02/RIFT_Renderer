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

#include "core/data_types/vec3.h"

image_texture::image_texture(unsigned char* pixels, int A, int B)
  : data(pixels)
  , nx(A)
  , ny(B)
{}

vec3 image_texture::value(float u, float v, const vec3& p) const
{
    int i = int((u)*nx);
    int j = int((1.f - v) * ny - 0.001f);
    if (i < 0)
    {
        i = 0;
    }
    if (j < 0)
    {
        j = 0;
    }
    if (i > nx - 1.f)
    {
        i = int(nx - 1.f);
    }
    if (j > ny - 1.f)
    {
        j = int(ny - 1.f);
    }
    float col_inv = 1.f / 255;
    float r = int(data[3 * i + 3 * nx * j]) * col_inv;
    float g = int(data[3 * i + 3 * nx * j + 1]) * col_inv;
    float b = int(data[3 * i + 3 * nx * j + 2]) * col_inv;
    return vec3(r, g, b);
}
