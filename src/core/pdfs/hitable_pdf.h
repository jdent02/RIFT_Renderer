#pragma once

#include "core/bases/ihitable.h"
#include "pdf.h"

class hitable_pdf : public pdf
{
  public:
    hitable_pdf(ihitable* p, const vec3& origin)
      : o(origin)
      , ptr(p)
    {}

    float value(const vec3& direction) const override
    {
        return ptr->pdf_value(o, direction);
    }

    vec3 generate() const override { return ptr->random(o); };

    vec3      o;
    ihitable* ptr;
};
