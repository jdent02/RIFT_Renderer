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

#include "core/data_types/vec3.h"
#include "core/rendering/utility_functions.h"

inline float trilinear_interp(vec3 c[2][2][2], float u, float v, float w)
{
    float uu = u * u * (3 - 2 * u);
    float vv = v * v * (3 - 2 * v);
    float ww = w * w * (3 - 2 * w);
    float accum = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1.f - i) * (1.f - uu)) *
                         (j * vv + (1.f - j) * (1.f - vv)) *
                         (k * ww + (1.f - k) * (1.f - ww)) *
                         dot(c[i][j][k], weight_v);
            }
        }
    }

    return accum;
}

static vec3* perlin_generate()
{
    vec3* p = new vec3[256];
    for (int i = 0; i < 256; ++i)
    {
        p[i] = unit_vector(vec3(
            -1 + 2 * (rand() * inv_rand_max),
            -1 + 2 * (rand() * inv_rand_max),
            -1 + 2 * (rand() * inv_rand_max)));
    }
    return p;
}

inline void permute(int* p, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int target = int(rand() * inv_rand_max * (i + 1));
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

static int* perlin_generate_perm()
{
    int* p = new int[256];
    for (int i = 0; i < 256; i++)
    {
        p[i] = i;
    }
    permute(p, 256);
    return p;
}

class perlin
{
  public:
    perlin()
      : ranvec(perlin_generate())
      , perm_x(perlin_generate_perm())
      , perm_y(perlin_generate_perm())
      , perm_z(perlin_generate_perm())
    {}

    float noise(const vec3& p) const;

    float turb(const vec3& p, float depth = 7) const;

    vec3* ranvec;
    int*  perm_x;
    int*  perm_y;
    int*  perm_z;
};

inline float perlin::noise(const vec3& p) const
{
    float u = p.x() - floor(p.x());
    float v = p.y() - floor(p.y());
    float w = p.z() - floor(p.z());
    int   i = floor(p.x());
    int   j = floor(p.y());
    int   k = floor(p.z());

    vec3 c[2][2][2];
    for (int di = 0; di < 2; di++)
    {
        for (int dj = 0; dj < 2; dj++)
        {
            for (int dk = 0; dk < 2; dk++)
            {
                c[di][dj][dk] = ranvec
                    [perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^
                     perm_z[(k + dk) & 255]];
            }
        }
    }

    return trilinear_interp(c, u, v, w);
}

inline float perlin::turb(const vec3& p, const float depth) const
{
    float accum = 0;
    vec3  temp_p = p;
    float weight = 1.f;
    for (int i = 0; i < depth; i++)
    {
        accum += weight * noise(temp_p);
        weight *= 0.5f;
        temp_p *= 2.;
    }
    return std::fabs(accum);
}
