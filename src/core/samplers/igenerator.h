#pragma once

#include <cstdint>

enum samplers
{
    XORO_128,
    RAND_48
};

class igenerator
{
  public:
    igenerator() = default;

    virtual ~igenerator() = default;

    virtual float get_1_d() = 0;

    virtual float get_2d() = 0;

    virtual void seed_gen(uint64_t seed) = 0;
};
