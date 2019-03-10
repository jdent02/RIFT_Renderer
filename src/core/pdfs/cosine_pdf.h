#pragma once

#include "core/pdfs/pdf.h"
#include "core/rendering/onb.h"

class cosine_pdf final : public pdf
{
  public:
    explicit cosine_pdf(const vec3& w) { uvw.build_from_w(w); }
    float value(const vec3& direction) const override;
    vec3  generate() const override;

    onb uvw;
};
