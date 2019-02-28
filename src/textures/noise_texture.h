#ifndef FARTS_RENDERER_NOISE_TEXTURE_H
#define FARTS_RENDERER_NOISE_TEXTURE_H

#include "texture.h"
#include "utility/data_types/vec3.h"
#include "utility/noises/perlin.h"


class noise_texture
    :public texture
{
  public:
    noise_texture() = default;

    explicit noise_texture(float sc): scale(sc) {};

    virtual vec3 value(
        float u,
        float v,
        const vec3& p) const override
    {
        return vec3(1.f, 1.f, 1.f) * 0.5f * (1 + noise.turb(scale * p));
//        return vec3(1.f, 1.f, 1.f) * noise.turb(scale * p);
//        return vec3(1.f, 1.f, 1.f) * 0.5f * (1 + sin(scale*p.z() + 10.f * noise.turb(p)));
    }

    perlin noise{};
    float scale{1.f};
};



#endif //FARTS_RENDERER_NOISE_TEXTURE_H
