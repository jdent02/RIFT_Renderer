#pragma once

#include "itexture.h"

class image_texture : public itexture
{
  public:
    image_texture() = default;

    image_texture(unsigned char* pixels, int A, int B);

    virtual vec3 value(float u, float v, const vec3& p) const override;

    unsigned char* data;
    int            nx, ny;
};
