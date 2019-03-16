// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// Local libraries
#include "core/samplers/rng/i_rand_generator.h"

// Standard libraries
#include <cstdint>

constexpr float inv_uint64 = 1.f / UINT64_MAX;

// Taken from Xoroshiro128
// Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

static uint64_t rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

class Xoro128 : public IRandGenerator
{
  public:
    // Constructors
    Xoro128() = default;

    // Destructor
    ~Xoro128() override = default;

    float get_1_d() override;

    void seed_gen(uint64_t seed) override;

    float get_2d() override { return 0.f; }

  private:
    uint64_t s[2]{0x46961B5E381BCE6EULL, 0x55897310023CAE21ULL};
};
