#pragma once


#include "texture.h"

#include <memory>

class vec3;

class checker_texture
    : public texture
{
public:
    checker_texture() = default;

    checker_texture(std::unique_ptr<texture> t0, std::unique_ptr<texture> t1)
        : odd(std::move(t1))
        , even(std::move(t0)) {};

    virtual ~checker_texture() override = default;

    virtual vec3 value(float u, float v, const vec3& p) const override;

    std::unique_ptr<texture> odd;
    std::unique_ptr<texture> even;
};
