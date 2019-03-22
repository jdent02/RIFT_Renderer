#include "utility/generators/scene_generator.h"
#include "core/rendering/render.h"

#include <iostream>
#include <sstream>
#include <ctime>



int main()
{
    const int nx{640};
    const int ny{480};
    const int num_samples(30 * 8);

    scene_generator generator;

    scene* scene = generator.make_random_scene(nx, ny);

    time_t start_time = time(NULL);

    std::cout << "Rendering....." << std::endl;

    renderer engine{
        nx,
        ny,
        num_samples,
        scene->cam,
        scene->world};

    engine.do_render();

    engine.write_JPEG();

    time_t end_time = time(NULL);

    std::cout << "Render Finished; Total Time: " << end_time - start_time << std::endl;
    return 0;
}
