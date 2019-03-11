#pragma once

#include "core/data_types/ray.h"
#include "core/pdfs/pdf.h"

#include <memory>

struct scatter_record
{
    ray                  specular_ray;
    bool                 is_specular;
    vec3                 attenuation;
    std::unique_ptr<pdf> pdf_ptr;
};
