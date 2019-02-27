#ifndef TEXTURE_H
#define TEXTURE_H

// Froward declaration
class vec3;

class texture
{
  public:
    virtual ~texture() = default;

    virtual vec3 value(
        float u,
        float v,
        const vec3& p) const = 0;
};

#endif // TEXTURE_H
