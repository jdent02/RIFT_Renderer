#pragma once

class mixture_pdf : public pdf
{
  public:
    mixture_pdf(pdf* p0, pdf* p1)
    {
        p[0] = p0;
        p[1] = p1;
    }

    float value(const vec3& direction) const override
    {
        return float(
            0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction));
    }

    vec3 generate() const override
    {
        if (rand() * (1.f / RAND_MAX) < 0.5)
        {
            return p[0]->generate();
        }
        return p[1]->generate();
    }

    pdf* p[2]{};
};
