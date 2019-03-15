#include "pathtracer.h"

#include "core/data_types/hit_record.h"
#include "core/data_types/scatter_record.h"
#include "core/pdfs/hitable_pdf.h"
#include "core/pdfs/mixture_pdf.h"
#include "core/rendering/utility_functions.h"
#include "materials/imaterial.h"

vec3 pathtracer::trace(
    const ray& r,
    ihitable*  world,
    ihitable*  light_shape,
    const int  depth) const
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
                       trace(srec.specular_ray, world, light_shape, depth + 1);
            }
            vec3  direction = srec.pdf_ptr.get()->generate();
            ray   scattered(hrec.p, direction, r.time());
            float pdf_val = srec.pdf_ptr.get()->value(scattered.direction());

            return emitted +
                   srec.attenuation *
                       hrec.mat_ptr->scattering_pdf(r, hrec, scattered) *
                       trace(scattered, world, light_shape, depth + 1) /
                       pdf_val;
        }
        return emitted;
    }
    return vec3(0.f, 0.f, 0.f);
}
