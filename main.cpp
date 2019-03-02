#include "utility/data_types/vec3.h"
#include "camera/camera.h"
#include "utility/generators/scene_generator.h"
#include "hitables/hitable.h"
#include "rendering/render.h"

#include <iostream>
#include <sstream>
#include <ctime>



int main()
{
    const int nx{480};
    const int ny{480};
    const int num_samples(200);

    const vec3 lookfrom(278.f, 278.f, -800.f);
    const vec3 lookat(278.f, 278.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    camera cam(
            lookfrom,
            lookat,
            vec3(0.f, 1.f, 0.f),
            40.f,
            float(nx) / float(ny),
            aperture,
            dist_to_focus,
            0.f,
            0.5f);

    scene_generator generator;

    hitable* world = generator.cornell_box();

    time_t start_time = time(NULL);

    std::cout << "Rendering....." << std::endl;

    renderer engine{
        nx,
        ny,
        num_samples,
        cam,
        world};

    engine.do_render();

    engine.write_buffer();

    time_t end_time = time(NULL);

    std::cout << "Render Finished; Total Time: " << end_time - start_time << std::endl;
    return 0;
}
