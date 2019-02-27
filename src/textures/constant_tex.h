#ifndef CONSTANT_TEX_H
#define CONSTANT_TEX_H


class constant_texture
    : public texture
{
  public:
    constant_texture() = default;

    explicit constant_texture(vec3 c)
        : color(c) {};

    virtual ~constant_texture() override = default;

    virtual vec3 value(float u, float v, const vec3& p) const override { return color; };

    vec3 color;
};

#endif // CONSTANT_TEX_H