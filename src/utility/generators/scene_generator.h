#pragma once

#include "hitables/ihitable.h"
#include "core/data_types/scene.h"
#include "utility/containers/render_settings.h"

// Utility function to generate a random scene
class scene_generator
{
  public:
    scene_generator() = default;

    ~scene_generator() = default;
    
    void make_random_scene(scene& in_scene, const render_settings& settings);
    
    // ihitable* two_spheres();
    //
    // scene* earth_sphere(int x_dim, int y_dim);
    //
    // scene* rect_light(int nx, int ny);

    void cornell_box(scene& in_scene, const render_settings& settings);
};
