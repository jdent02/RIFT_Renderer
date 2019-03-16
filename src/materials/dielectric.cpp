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

#include "dielectric.h"

#include "core/data_types/ray.h"
#include "core/rendering/scatter_functions.h"
#include "core/rendering/utility_functions.h"

bool dielectric::scatter(
    const ray&        r_in,
    const hit_record& rec,
    scatter_record&   srec) const
{
    vec3 outward_normal;

    float ni_over_nt;

    const vec3 reflected = reflect(r_in.direction(), rec.normal);
    srec.attenuation = vec3(1.f, 1.f, 1.f);
    vec3 refracted;

    float reflect_prob;
    float cosine;

    if (dot(r_in.direction(), rec.normal) > 0)
    {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(), rec.normal) /
                 r_in.direction().length();
    }
    else
    {
        outward_normal = rec.normal;
        ni_over_nt = 1.f / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }

    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
        reflect_prob = schlick(cosine, ref_idx);
    }
    else
    {
        srec.specular_ray = ray(rec.p, reflected, r_in.time());
        reflect_prob = 1.f;
    }

    if (rand() * inv_rand_max < reflect_prob)
    {
        srec.specular_ray = ray(rec.p, reflected, r_in.time());
        srec.is_specular = true;
    }
    else
    {
        srec.specular_ray = ray(rec.p, refracted, r_in.time());
        srec.is_specular = true;
    }

    return true;
}
