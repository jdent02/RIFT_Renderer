#pragma once


#include <cstdint>

class igenerator
{
  public:
    igenerator() = default;

    virtual ~igenerator() = default;

    virtual float next() = 0;

    virtual void seed_gen(uint64_t seed) = 0;
};

