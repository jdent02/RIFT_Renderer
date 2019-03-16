#include "command_line_parser.h"

#include "utility/containers/scene.h"
#include "core/rendering/render_controller.h"
#include "utility/containers/render_settings.h"
#include "utility/generators/scene_generator.h"

#include <cstdio>
#include <ctime>
#include <memory>

int main(const int argc, char* argv[])
{
    command_line_parser parser;

    render_settings settings = parser.parse(argc, argv);

    std::unique_ptr<scene_generator> generator = std::make_unique<scene_generator>();

    std::unique_ptr<scene> master_scene = std::make_unique<scene>();

    generator->make_random_scene(master_scene.get(), settings);

    const time_t start_time = time(nullptr);

    std::unique_ptr<render_controller> engine = std::make_unique<render_controller>(settings, master_scene.get());

    engine->do_render();

    engine->write_output();

    const time_t end_time = time(nullptr);

    printf("Render Finished; Total Time: %f\n", static_cast<double>(end_time - start_time));
     
    return 0;
}
