#include "metal.h"

#include "core/rendering/scatter_functions.h"
#include "core/rendering/utility_functions.h"

bool metal::scatter(
    const ray&        r_in,
    const hit_record& hrec,
    scatter_record&   srec) const
{
    const vec3 reflected = reflect(unit_vector(r_in.direction()), hrec.normal);
    srec.specular_ray = ray(hrec.p, reflected + fuzz * random_in_unit_sphere());
    srec.attenuation = albedo;
    srec.is_specular = true;
    srec.pdf_ptr = nullptr;
    return true;
}
