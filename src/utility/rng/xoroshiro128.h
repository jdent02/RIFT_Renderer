#ifndef XOROSHIRO128_H
#define XOROSHIRO128_H

#include <cstdint>

//  Adapted from xoroshiro128
//  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

static uint64_t rotl(const uint64_t x, int k)
{
    return x << k | x >> 64 - k;
}

class xoro128
{
public:
    xoro128();
    xoro128(uint64_t seed_1, uint64_t seed_2);
    float get_num();
private:
    uint64_t s[2] {0x46961b5e381bce6eull, 0x55897310023cae21ull};
};

inline xoro128::xoro128(uint64_t seed_1, uint64_t seed_2)
{
    s[0] = seed_1;
    s[1] = seed_2;
}

inline float xoro128::get_num() {
	const uint64_t s0 = s[0];
	uint64_t s1 = s[1];
	const uint64_t result = rotl(s0 * 5, 7) * 9;

	s1 ^= s0;
	s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
	s[1] = rotl(s1, 37); // c

	return float(result);
}

#endif // XOROSHIRO128_H
