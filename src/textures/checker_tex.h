#ifndef FARTS_CHECKER_TEX
#define FARTS_CHECKER_TEX

#include "texture.h"

class checker_texture
    : public texture
{
public:
    checker_texture() = default;
    checker_texture(texture *t0, texture *t1) : odd(t1), even(t0) {};
    virtual ~checker_texture() override = default;
    virtual vec3 value(float u, float v, const vec3& p) const override;

    texture* odd;
    texture* even;
};


#endif FARTS_CHECKER_TEX