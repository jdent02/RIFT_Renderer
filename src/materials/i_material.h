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
#include "core/data_types/vec3.h"
#include "core/data_types/hit_record.h"
#include "core/data_types/scatter_record.h"

class IMaterial
{
  public:
    virtual ~IMaterial() = default;

    virtual bool pdf_based_scatter(
        const Ray&       r_in,
        const HitRecord& hrec,
        ScatterRecord&   srec) const
    {
        return false;
    }

    virtual float scattering_pdf(
        const Ray&       r_in,
        const HitRecord& hrec,
        const Ray&       scattered) const
    {
        return false;
    }

    virtual Vec3 emitted(
        const Ray&       r_in,
        const HitRecord& rec,
        float            u,
        float            v,
        const Vec3&      p) const
    {
        return Vec3(0.f, 0.f, 0.f);
    }

    virtual Vec3 path_emitted(float u, float v, const Vec3& p) const
    {
        return Vec3(0.f, 0.f, 0.f);
    }

    virtual bool path_scatter(
        const Ray&       r_in,
        const HitRecord& rec,
        Vec3&            attenuation,
        Ray&             scattered) const
    {
        return false;
    };
};
