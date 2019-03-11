#include "lambertian.h"

#include "core/pdfs/cosine_pdf.h"
#include "core/rendering/utility_functions.h"

bool lambertian::scatter(
    const ray&        r_in,
    const hit_record& hrec,
    scatter_record&   srec) const
{
    srec.is_specular = false;
    srec.attenuation = albedo->value(hrec.u, hrec.v, hrec.p);
    srec.pdf_ptr = std::make_unique<cosine_pdf>(hrec.normal);
    return true;
}

float lambertian::scattering_pdf(
    const ray&        r_in,
    const hit_record& rec,
    const ray&        scattered) const
{
    float cosine = dot(rec.normal, unit_vector(scattered.direction()));
    if (cosine < 0)
    {
        cosine = 0;
    }

    return cosine * inv_pi;
}
