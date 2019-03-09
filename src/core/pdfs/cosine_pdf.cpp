#include "cosine_pdf.h"

#include "core/rendering/utility_functions.h"

float cosine_pdf::value(const vec3& direction) const
{
    float cosine = dot(unit_vector(direction), uvw.w());
    if (cosine > 0)
    {
        return cosine * inv_pi;
    }
    return 0;
}

vec3 cosine_pdf::generate() const
{
    return uvw.local(random_cosine_direction());
}
