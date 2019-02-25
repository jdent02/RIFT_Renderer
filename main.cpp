#include "utility/vec3.h"
#include "camera/camera.h"
#include "utility/generators.h"
#include "hitables/hitable.h"
#include "rendering/render.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>



int main()
{
    const int nx{640};
    const int ny{480};
    const int num_samples(5);

    const float inv_nx = 1.f / nx;
    const float inv_ny = 1.f / ny;

    const vec3 lookfrom(-1.f, 1.75f, 8.f);
    const vec3 lookat(0.f, 0.5f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.1f;

    camera cam(
        lookfrom,
        lookat,
        vec3(0.f, 1.f, 0.f), 
        35.f, 
        float(nx)/float(ny),
        aperture,
        dist_to_focus);

    scene_generator generator;

    hitable* world = generator.make_random_scene();

    std::vector<std::vector<int>> buffer;

    time_t start_time = time(NULL);

    std::cout << "Rendering....." << std::endl;

    renderer engine;

    engine.do_render(
        buffer, 
        nx, 
        ny, 
        num_samples, 
        inv_nx, 
        inv_ny, 
        cam, 
        world);

    engine.write_buffer(buffer, nx, ny);

    time_t end_time = time(NULL);

    std::cout << "Render Finished; Total Time: " << end_time - start_time << std::endl;
    return 0;
}
