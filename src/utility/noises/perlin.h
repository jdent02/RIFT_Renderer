#ifndef FARTS_RENDERER_PERLIN_H
#define FARTS_RENDERER_PERLIN_H


#include "utility/utility_functions.h"
#include "utility/data_types/vec3.h"

inline float trilinear_interp(
    vec3 c[2][2][2],
    float u,
    float v,
    float w)
{
    float uu = u * u * (3 - 2 * u);
    float vv = v * v * (3 - 2 * v);
    float ww = w * w * (3 - 2 * w);
    float accum = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                vec3 weight_v(u - i, v - j, w - k);
                accum += (i * u + (1.f - i) * (1.f - u)) *
                         (j * v + (1.f - j) * (1.f - v)) *
                         (k * w + (1.f - k) * (1.f - w)) * dot(c[i][j][k], weight_v);
            }
        }
    }


    return accum;
}

static vec3* perlin_generate()
{
    vec3* p = new vec3[256];
    for (int i = 0; i < 256; ++i)
    {
        p[i] = unit_vector(
            vec3(
                -1 + 2 * (rand() * inv_rand_max),
                -1 + 2 * (rand() * inv_rand_max),
                -1 + 2 * (rand() * inv_rand_max)));
    }
    return p;
}

inline void permute(int* p, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int target = int(rand() * inv_rand_max * (i + 1));
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

static int* perlin_generate_perm()
{
    int* p = new int[256];
    for (int i = 0; i < 256; i++)
    {
        p[i] = i;
    }
    permute(p, 256);
    return p;
}


class perlin
{
  public:
    perlin()
        : ranvec(perlin_generate()),
          perm_x(perlin_generate_perm()),
          perm_y(perlin_generate_perm()),
          perm_z(perlin_generate_perm()) {}

    float noise(const vec3& p) const;

    float turb(const vec3& p, const float depth=7) const;

    vec3* ranvec;
    int* perm_x;
    int* perm_y;
    int* perm_z;
};

inline float perlin::noise(const vec3& p) const
{
    float u = p.x() - floor(p.x());
    float v = p.y() - floor(p.y());
    float w = p.z() - floor(p.z());
    int i = floor(p.x());
    int j = floor(p.y());
    int k = floor(p.z());

    vec3 c[2][2][2];
    for (int di = 0; di < 2; di++)
    {
        for (int dj = 0; dj < 2; dj++)
        {
            for (int dk = 0; dk < 2; dk++)
            {
                c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^
                                       perm_y[(j + dj) & 255] ^
                                       perm_z[(k + dk) & 255]];
            }
        }
    }

    return trilinear_interp(c, u, v, w);
}

float perlin::turb(const vec3& p, const float depth) const
{
    float accum = 0;
    vec3 temp_p = p;
    float weight = 1.f;
    for (int i = 0; i < depth; i++)
    {
        accum += weight*noise(temp_p);
        weight *= 0.5f;
        temp_p *= 2.;
    }
    return std::fabs(accum);
}


#endif //FARTS_RENDERER_PERLIN_H
