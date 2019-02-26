#include "xoroshiro128.h"

xoro_128::xoro_128(const uint64_t s0, const uint64_t s1)
{
    s[0] = s0;
    s[1] = s1;
}

uint64_t xoro_128::next()
{
    const uint64_t s0 = s[0];
    uint64_t s1 = s[1];
    const uint64_t result = rotl(s0 * 5, 7) * 9;

    s1 ^= s0;
    s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
    s[1] = rotl(s1, 37); // c

    return result;
}

void xoro_128::jump()
{
    const uint64_t JUMP[] = {0xdf900294d8f554a5, 0x170865df4b3201fc};

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    for (unsigned long long i : JUMP)
    {
        for (int b = 0; b < 64; b++)
        {
            if (i & UINT64_C(1) << b)
            {
                s0 ^= s[0];
                s1 ^= s[1];
            }
            next();
        }
    }

    s[0] = s0;
    s[1] = s1;
}

void xoro_128::long_jump()
{
    const uint64_t LONG_JUMP[] = {0xd2a98b26625eee7b, 0xdddf9b1090aa7ac1};

    uint64_t s0 = 0;
    uint64_t s1 = 0;
    for (unsigned long long i : LONG_JUMP)
    {
        for (int b = 0; b < 64; b++)
        {
            if (i & UINT64_C(1) << b)
            {
                s0 ^= s[0];
                s1 ^= s[1];
            }
            next();
        }
    }

    s[0] = s0;
    s[1] = s1;
}