#ifndef XORO_128
#define XORO_128

#include <stdint.h>

#define INV_UINT_MAX 1.f / UINT64_MAX;

// Taken from Xoroshiro128
// Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)


static inline uint64_t rotl(const uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

class xoro_128
{
  public:
    // Constructors
    xoro_128() = default;
    xoro_128(uint64_t s0, uint64_t s1);

    // Destructor
    ~xoro_128() = default;

	uint64_t next();
	void jump();
	void long_jump();

  private:
    uint64_t s[2] {0x46961B5E381BCE6EULL, 0x55897310023CAE21ULL};
};

#endif // XORO_128
