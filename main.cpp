#include "utility/generators/scene_generator.h"
#include "core/data_types/scene.h"
#include "core/rendering/render_controller.h"

#include <iostream>
#include <sstream>
#include <ctime>



int main()
{
    const int nx{640};
    const int ny{480};
    const int num_samples(50 * 8);

    scene_generator generator;

    scene* scene = generator.make_random_scene(nx, ny);

    time_t start_time = time(NULL);

    std::cout << "Rendering....." << std::endl;

    render_controller* engine = new render_controller{
        "../image.jpg",
        nx,
        ny,
        num_samples,
        scene->cam,
        scene->world};

    engine->do_render();

    engine->write_output();

    engine->cleanup();

    delete engine;
    delete scene;

    time_t end_time = time(NULL);

    std::cout << "Render Finished; Total Time: " << end_time - start_time << std::endl;
    return 0;
}
