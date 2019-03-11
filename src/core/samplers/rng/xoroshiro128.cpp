#include "xoroshiro128.h"

float xoro_128::get_1_d()
{
    const uint64_t s0 = s[0];
    uint64_t       s1 = s[1];
    const uint64_t result = rotl(s0 * 5, 7) * 9;

    s1 ^= s0;
    s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
    s[1] = rotl(s1, 37);                   // c

    return result * inv_uint64;
}

void xoro_128::seed_gen(const uint64_t seed)
{
    s[0] = seed;
    s[1] = seed << 16;
}
