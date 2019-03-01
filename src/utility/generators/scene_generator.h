#ifndef FARTS_GENERATORS
#define FARTS_GENERATORS


#include <hitables/hitable.h>


// Utility function to generate a random scene
class scene_generator
{
  public:
    scene_generator() = default;

    ~scene_generator() = default;

    hitable* make_random_scene();

    hitable* two_spheres();

    hitable* earth_sphere();

    hitable* rect_light();
};

#endif