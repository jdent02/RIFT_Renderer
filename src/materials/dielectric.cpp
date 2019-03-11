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
