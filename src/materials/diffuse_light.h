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
#include "core/data_types/vec3.h"
#include "imaterial.h"
#include "textures/itexture.h"

class diffuse_light : public imaterial
{
  public:
    explicit diffuse_light(itexture* a)
      : emit(a){};

    ~diffuse_light() override = default;

    bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec)
        const override
    {
        return false;
    }

    virtual vec3 emitted(
        const ray&        r_in,
        const hit_record& rec,
        float             u,
        float             v,
        const vec3&       p) const override
    {
        if (dot(rec.normal, r_in.direction()) < 0.0)
        {
            return emit->value(u, v, p);
        }
        return vec3(0.f, 0.f, 0.f);
    }

    itexture* emit;
};
