#include "core/data_types/scene.h"
#include "core/rendering/render_controller.h"
#include "utility/containers/render_settings.h"
#include "utility/generators/scene_generator.h"
#include "utility/parsers/command_line_parser.h"

#include <ctime>
#include <iostream>
#include <sstream>

int main(const int argc, char* argv[])
{
    command_line_parser parser;

    const render_settings settings = parser.parse(argc, argv);

    scene_generator generator;

    scene master_scene{};

    generator.cornell_box(master_scene, settings);

    const time_t start_time = time(nullptr);

    std::cout << "Rendering....." << std::endl;

    render_controller engine(settings, &master_scene);

    engine.do_render();

    engine.write_output();

    const time_t end_time = time(nullptr);

    std::cout << "Render Finished; Total Time: " << end_time - start_time
              << std::endl;
    
    return 0;
}
