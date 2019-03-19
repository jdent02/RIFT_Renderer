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

#include "core/data_types/ray.h"

#include <cmath>

// global const variables
#define INV_RAND_MAX float(1.f / RAND_MAX)
#define FLOAT_M_PI float(M_PI)
#define INV_PI (1.f / FLOAT_M_PI)

inline Vec3 random_cosine_direction()
{
    float r1 = rand() * INV_RAND_MAX;
    float r2 = rand() * INV_RAND_MAX;
    float z = std::sqrt(1 - r2);
    float phi = 2 * FLOAT_M_PI * r1;
    float x = cos(phi) * 2 * std::sqrt(r2);
    float y = sin(phi) * 2 * std::sqrt(r2);
    return Vec3(x, y, z);
}

inline Vec3 random_in_unit_sphere()
{
    Vec3 p;
    do
    {
        p = 2.f * Vec3(
                      rand() * INV_RAND_MAX,
                      rand() * INV_RAND_MAX,
                      rand() * INV_RAND_MAX) -
            Vec3(1.f, 1.f, 1.f);
    } while (dot(p, p) >= 1.f);

    return p;
}

inline Vec3 random_on_unit_sphere()
{
    Vec3 p;
    do
    {
        p = 2.f * Vec3(
                      rand() * INV_RAND_MAX,
                      rand() * INV_RAND_MAX,
                      rand() * INV_RAND_MAX) -
            Vec3(1.f, 1.f, 1.f);
    } while (dot(p, p) >= 1.f);

    return unit_vector(p);
}

inline Vec3 random_to_sphere(const float radius, const float distance_squared)
{
    float r1 = rand() * INV_RAND_MAX;
    float r2 = rand() * INV_RAND_MAX;
    float z = 1 + r2 * (std::sqrt(1 - radius * radius / distance_squared) - 1);
    float phi = 2 * FLOAT_M_PI * r1;
    float x = cos(phi) * std::sqrt(1 - z * z);
    float y = sin(phi) * std::sqrt(1 - z * z);
    return Vec3(x, y, z);
}

inline Vec3 random_in_unit_disk()
{
    Vec3 p;
    do
    {
        p = 2.f * Vec3(rand() * INV_RAND_MAX, rand() * INV_RAND_MAX, 0.f) -
            Vec3(1.f, 1.f, 0.f);
    } while (dot(p, p) >= 1.f);

    return p;
}
