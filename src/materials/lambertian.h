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

#include "core/data_types/hit_record.h"
#include "materials/i_material.h"
#include "textures/i_texture.h"

struct ScatterRecord;

class Lambertian : public IMaterial
{
  public:
    explicit Lambertian(ITexture* a)
      : m_albedo_(a){};

    ~Lambertian() = default;

    bool pdf_based_scatter(
        const Ray&       r_in,
        const HitRecord& hrec,
        ScatterRecord&   srec) const override;

    float scattering_pdf(
        const Ray&       r_in,
        const HitRecord& rec,
        const Ray&       scattered) const override;

    bool path_scatter(
        const Ray&       r_in,
        const HitRecord& rec,
        Vec3&            attenuation,
        Ray&             scattered) const override;

  private:
    ITexture* m_albedo_;
};
