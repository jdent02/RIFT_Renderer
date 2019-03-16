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
constexpr float inv_rand_max = 1.f / RAND_MAX;
constexpr float pi = 3.14159f;
constexpr float inv_pi = 1.f / 3.14159f;

inline vec3 random_cosine_direction()
{
    float r1 = rand() * inv_rand_max;
    float r2 = rand() * inv_rand_max;
    float z = std::sqrt(1 - r2);
    float phi = 2 * pi * r1;
    float x = cos(phi) * 2 * std::sqrt(r2);
    float y = sin(phi) * 2 * std::sqrt(r2);
    return vec3(x, y, z);
}

inline vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(
                      rand() * inv_rand_max,
                      rand() * inv_rand_max,
                      rand() * inv_rand_max) -
            vec3(1.f, 1.f, 1.f);
    } while (dot(p, p) >= 1.f);

    return p;
}

inline vec3 random_on_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(
                      rand() * inv_rand_max,
                      rand() * inv_rand_max,
                      rand() * inv_rand_max) -
            vec3(1.f, 1.f, 1.f);
    } while (dot(p, p) >= 1.f);

    return unit_vector(p);
}

inline vec3 random_to_sphere(const float radius, const float distance_squared)
{
    float r1 = rand() * inv_rand_max;
    float r2 = rand() * inv_rand_max;
    float z = 1 + r2 * (std::sqrt(1 - radius * radius / distance_squared) - 1);
    float phi = 2 * pi * r1;
    float x = cos(phi) * std::sqrt(1 - z * z);
    float y = sin(phi) * std::sqrt(1 - z * z);
    return vec3(x, y, z);
}

inline vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.f * vec3(rand() * inv_rand_max, rand() * inv_rand_max, 0.f) -
            vec3(1.f, 1.f, 0.f);
    } while (dot(p, p) >= 1.f);

    return p;
}
