#pragma once


#include "camera/camera.h"
#include "core/bases/hitable.h"


struct scene
{
    camera* cam;
    hitable* world;
};


// Utility function to generate a random scene
class scene_generator
{
public:
    scene_generator() = default;

    ~scene_generator() = default;

    scene* make_random_scene(int nx, int ny);

    hitable* two_spheres();

    scene* earth_sphere(int x_dim, int y_dim);

    scene* rect_light(int nx, int ny);

    scene* cornell_box(int nx, int ny);
};
