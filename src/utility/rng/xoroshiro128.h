#pragma once

// Local libraries
#include "igenerator.h"

// Standard libraries
#include <cstdint>

// Taken from Xoroshiro128
// Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

static inline uint64_t rotl(
    const uint64_t x,
    int k)
{
    return (x << k) | (x >> (64 - k));
}

class xoro_128
    : public igenerator
{
  public:
    // Constructors
    xoro_128() = default;

    // Destructor
    ~xoro_128() override = default;

    virtual float next() override;

    virtual void seed_gen(uint64_t seed) override;

  private:
    uint64_t s[2]{0x46961B5E381BCE6EULL, 0x55897310023CAE21ULL};
};
