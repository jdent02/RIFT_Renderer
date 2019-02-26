#ifndef FARTS_GENERATORS
#define FARTS_GENERATORS

#include "hitables/hitable_list.h"

// Utility function to generate a random scene
class scene_generator
{
public:
    scene_generator() = default;
    ~scene_generator() = default;
    hitable *make_random_scene();
};

#endif