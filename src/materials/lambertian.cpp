#include "lambertian.h"

#include "core/rendering/onb.h"
#include "core/rendering/utility_functions.h"

bool lambertian::scatter(
    const ray&        r_in,
    const hit_record& rec,
    vec3&             alb,
    ray&              scattered,
    float&            pdf) const
{
    onb uvw;
    uvw.build_from_w(rec.normal);
    vec3 direction = uvw.local(random_cosine_direction());
    scattered = ray(rec.p, unit_vector(direction), r_in.time());
    alb = albedo->value(rec.u, rec.v, rec.p);
    pdf = dot(uvw.w(), scattered.direction()) * inv_pi;
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
