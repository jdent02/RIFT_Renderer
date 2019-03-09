#include "command_line_parser.h"

#include "core/data_types/scene.h"
#include "core/rendering/render_controller.h"
#include "utility/containers/render_settings.h"
#include "utility/generators/scene_generator.h"

#include <cstdio>
#include <ctime>

int main(const int argc, char* argv[])
{
    command_line_parser parser;

    const render_settings settings = parser.parse(argc, argv);

    scene_generator generator;

    scene master_scene{};

    generator.cornell_box(master_scene, settings);

    const time_t start_time = time(nullptr);

    printf("Rendering.....\n");

    render_controller engine(settings, master_scene);

    engine.do_render();

    engine.write_output();

    const time_t end_time = time(nullptr);

    printf("Render Finished; Total Time: %f\n", static_cast<double>(end_time - start_time));
     
    return 0;
}
