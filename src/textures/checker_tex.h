#ifndef CHECKER_TEX_H
#define CHECKER_TEX_H

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
#endif // CHECKER_TEX_H
