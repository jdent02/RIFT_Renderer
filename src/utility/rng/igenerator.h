#ifndef FARTS_RENDERER_GENERATOR_H
#define FARTS_RENDERER_GENERATOR_H

#include <cstdint>

class igenerator
{
  public:
    igenerator() = default;

    virtual ~igenerator() = default;

    virtual float next() = 0;

    virtual void seed_gen(uint64_t seed) = 0;
};

#endif //FARTS_RENDERER_GENERATOR_H
