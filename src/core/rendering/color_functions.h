#pragma once

#include "materials/imaterial.h"

#include <cfloat>
#include <core/data_types/ray.h>
#include <core/data_types/vec3.h>
#include <core/pdfs/hitable_pdf.h>
#include <core/pdfs/mixture_pdf.h>
#include <hitables/ihitable.h>
#include <hitables/rect.h>

inline vec3 color(
    const ray& r,
    ihitable*  world,
    ihitable*  light_shape,
    const int  depth)
{
    hit_record hrec;
    if (world->hit(r, 0.001f, FLT_MAX, hrec))
    {
        scatter_record srec;
        const vec3     emitted =
            hrec.mat_ptr->emitted(r, hrec, hrec.u, hrec.v, hrec.p);

        if (depth < 10 && hrec.mat_ptr->scatter(r, hrec, srec))
        {
            if (srec.is_specular)
            {
                return srec.attenuation *
                       color(srec.specular_ray, world, light_shape, depth + 1);
            }
            hitable_pdf plight(light_shape, hrec.p);
            mixture_pdf p(&plight, srec.pdf_ptr.get());
            ray         scattered(hrec.p, p.generate(), r.time());
            float       pdf_val = p.value(scattered.direction());

            return emitted +
                   srec.attenuation *
                       hrec.mat_ptr->scattering_pdf(r, hrec, scattered) *
                       color(scattered, world, light_shape, depth + 1) /
                       pdf_val;
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
