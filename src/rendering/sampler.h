#ifndef FARTS_RENDERER_SAMPLE_GENERATOR_H
#define FARTS_RENDERER_SAMPLE_GENERATOR_H

#include "utility/rng/xoroshiro128.h"
#include "utility/rng/generator.h"

#include <memory>

enum sample_generator_types
{
    XORO_128,
    RAND_48
};

class sampler
{
  public:
    sampler() = default;
    explicit sampler(sample_generator_types sample_generator_choice);
    std::unique_ptr<generator> random_generator;
};

inline sampler::sampler(sample_generator_types sample_generator_choice)
{
    if (sample_generator_choice == XORO_128)
    {
        random_generator = std::make_unique<xoro_128>();
    }
}


#endif //FARTS_RENDERER_SAMPLE_GENERATOR_H
