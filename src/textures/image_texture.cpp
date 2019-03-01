#include "image_texture.h"

#include "utility/data_types/vec3.h"

image_texture::image_texture(unsigned char* pixels, int A, int B)
    : data(pixels), nx(A), ny(B) {}

vec3 image_texture::value(
    float u,
    float v,
    const vec3& p) const
{
    int i = int((u) * nx);
    int j = int((1.f - v) * ny - 0.001f);
    if (i < 0)
    {
        i = 0;
    }
    if (j < 0)
    {
        j = 0;
    }
    if (i > nx - 1.f)
    {
        i = int(nx - 1.f);
    }
    if (j > ny - 1.f)
    {
        j = int(ny - 1.f);
    }
    float col_inv = 1.f / 255;
    float r = int(data[3 * i + 3 * nx * j]) * col_inv;
    float g = int(data[3 * i + 3 * nx * j + 1]) * col_inv;
    float b = int(data[3 * i + 3 * nx * j + 2]) * col_inv;
    return vec3(r, g, b);
}
