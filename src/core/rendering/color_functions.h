#pragma once

#include "materials/imaterial.h"

#include <core/data_types/vec3.h>
#include <core/data_types/ray.h>
#include <hitables/ihitable.h>
#include <cfloat>
#include <cmath>
#include <hitables/rect.h>
#include <core/pdfs/hitable_pdf.h>
#include <core/pdfs/cosine_pdf.h>
#include <core/pdfs/mixture_pdf.h>


inline vec3 color(const ray& r, ihitable* world, const int depth)
{
    hit_record rec;

    if (world->hit(r, 0.001f, FLT_MAX, rec))
    {
        ray scattered;

        const vec3 emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);

        vec3 albedo;

        float pdf_val;

        if (depth < 10 &&
            rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf_val))
        {
            xz_rect     light_shape(213, 343, 227, 332, 554, 0);
            hitable_pdf p0(&light_shape, rec.p);
            cosine_pdf  p1(rec.normal);
            mixture_pdf p(&p0, &p1);
            scattered = ray(rec.p, p.generate(), r.time());
            pdf_val = p.value(scattered.direction());

            return emitted +
                   albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered) *
                       color(scattered, world, depth + 1) / pdf_val;
        }
        return emitted;
    }
    return vec3(0.f, 0.f, 0.f);
}

inline vec3 de_nan(const vec3& c)
{
    vec3 temp = c;
    if (!(temp[0] == temp[0]))
    {
        temp[0] = 0;
    }
    if (!(temp[1] == temp[1]))
    {
        temp[1] = 0;
    }
    if (!(temp[2] == temp[2]))
    {
        temp[2] = 0;
    }

    return temp;
}