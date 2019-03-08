#include "core/data_types/scene.h"
#include "core/rendering/render_controller.h"
#include "utility/generators/scene_generator.h"

#include <ctime>
#include <iostream>
#include <sstream>

int main()
{
    const int nx{640};
    const int ny{640};
    const int num_samples(10 * 8);

    scene_generator generator;

    scene master_scene{};

    generator.make_random_scene(master_scene, nx, ny);

    const time_t start_time = time(nullptr);

    std::cout << "Rendering....." << std::endl;

    render_controller engine(
        "../image.png",
        nx,
        ny,
        num_samples,
        &master_scene);

    engine.do_render();

    engine.write_output();


    const time_t end_time = time(nullptr);

    std::cout << "Render Finished; Total Time: " << end_time - start_time
              << std::endl;
    return 0;
}
