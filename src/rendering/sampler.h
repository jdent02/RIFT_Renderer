#ifndef FARTS_RENDERER_SAMPLE_GENERATOR_H
#define FARTS_RENDERER_SAMPLE_GENERATOR_H

#include "utility/rng/drand48.h"
#include "utility/rng/xoroshiro128.h"

#include <memory>

// Forward declarations
class igenerator;

enum sample_generator_types
{
    XORO_128_GEN,
    DRAND_48_GEN
};

class sampler
{
  public:
    sampler() = default;

    explicit sampler(sample_generator_types sample_generator_choice);

    std::unique_ptr<igenerator> random_generator;
};

inline sampler::sampler(const sample_generator_types sample_generator_choice)
{
    if (sample_generator_choice == XORO_128_GEN)
    {
        random_generator = std::make_unique<xoro_128>();
    }
    else if (sample_generator_choice == DRAND_48_GEN)
    {
        random_generator = std::make_unique<drand_48>();
    }
}

#endif //FARTS_RENDERER_SAMPLE_GENERATOR_H