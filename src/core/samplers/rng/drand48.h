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

#include "core/samplers/rng/i_rand_generator.h"

#include <cstdint>

#define RAND48_SEED_0 0x330e
#define RAND48_SEED_1 0xabcd
#define RAND48_SEED_2 0x1234
#define RAND48_MULT_0 0xe66d
#define RAND48_MULT_1 0xdeec
#define RAND48_MULT_2 0x0005
#define RAND48_ADD 0x000b

class DRand48 : public IRandGenerator
{
  public:
    DRand48() = default;

    ~DRand48() override = default;

    float get_1_d() override
    {
        return static_cast<float>(erand48(rand48_seed));
    }

    void seed_gen(uint64_t seed) override;

    double erand48(unsigned short xseed[3]);

    void dorand48(unsigned short xseed[3]);

    float get_2d() override { return 0.f; }

    // Properties
    unsigned short rand48_seed[3] = {RAND48_SEED_0,
                                     RAND48_SEED_1,
                                     RAND48_SEED_2};
    unsigned short rand48_mult[3] = {RAND48_MULT_0,
                                     RAND48_MULT_1,
                                     RAND48_MULT_2};
    unsigned short rand48_add = RAND48_ADD;
};
