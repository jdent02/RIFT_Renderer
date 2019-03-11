#pragma once

// Local libraries
#include "core/samplers/igenerator.h"

// Standard libraries
#include <cstdint>

constexpr float inv_uint64 = 1.f / UINT64_MAX;

// Taken from Xoroshiro128
// Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

static uint64_t rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

class xoro_128 : public igenerator
{
  public:
    // Constructors
    xoro_128() = default;

    // Destructor
    ~xoro_128() override = default;

    float get_1_d() override;

    void seed_gen(uint64_t seed) override;

    float get_2d() override { return 0.f; }

  private:
    uint64_t s[2]{0x46961B5E381BCE6EULL, 0x55897310023CAE21ULL};
};