#pragma once

#include "igenerator.h"

#include <memory>

class sampler
{
  public:
    std::unique_ptr<igenerator> rand_gen;
    std::unique_ptr<igenerator> monte_carlo_gen;
};
