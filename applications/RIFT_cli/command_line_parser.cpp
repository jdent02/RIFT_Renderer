#include "command_line_parser.h"

#include "core/image_writers/ioutput_writer.h"
#include "core/samplers/igenerator.h"
#include "utility/containers/render_settings.h"
#include "utility/version/version.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <thread>

render_settings command_line_parser::parse(const int argc, char* argv[])
{
    int temp_threads{static_cast<int>(std::thread::hardware_concurrency())};
    samplers            sampler{XORO_128};
    int                 x_res{1920};
    int                 y_res{1080};
    lighting_integrator light_integrator{LIGHT_SAMPLE_PATH_TRACING};
    output_writers      out_writer{PNG};
    int                 samples{100};
    bool                use_importance_sampling{true};
    std::string         filepath{"../image_vcpp"};

    for (int i = 0; i < argc; i++)
    {
        if (!static_cast<bool>(strcmp(argv[i], "--threads")))
        {
            char*  threads = argv[i + 1];
            size_t str_len = strlen(threads);
            temp_threads = convert_number(str_len, threads);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--resolution")))
        {
            char*  x = argv[i + 1];
            size_t x_len = strlen(x);
            x_res = convert_number(x_len, x);
            char*  y = argv[i + 2];
            size_t y_len = strlen(y);
            y_res = convert_number(y_len, y);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--filepath")))
        {
            filepath = argv[i + 1];
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--samples")))
        {
            char*  sample_num = argv[i + 1];
            size_t str_len = strlen(sample_num);
            samples = convert_number(str_len, sample_num);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--integrator")))
        {
            if (!static_cast<bool>(strcmp(argv[i + 1], "path")))
            {
                light_integrator = PATH_TRACING;
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "light_sample")))
            {
                light_integrator = LIGHT_SAMPLE_PATH_TRACING;
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "direct")))
            {
                light_integrator = DIRECT_LIGHTING;
            }
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--help")))
        {
            print_help();
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--writer")))
        {
            if (!static_cast<bool>(strcmp(argv[i + 1], "jpeg")))
            {
                out_writer = JPEG;
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "open_exr")))
            {
                out_writer = OPENEXR;
            }
        }
    }

    printf(
        "Render Settings:\n"
        "Resolution: %i %i\n"
        "Number of Samples: %i\n"
        "Rendering Threads: %i\n",
        x_res,
        y_res,
        samples,
        temp_threads);

    return render_settings{x_res,
                           y_res,
                           samples,
                           light_integrator,
                           temp_threads,
                           sampler,
                           out_writer,
                           filepath,
                           use_importance_sampling};
}

int command_line_parser::convert_number(size_t& length, const char* number)
{
    int digit{0};

    for (size_t i = 0; i < length - 1; i++)
    {
        digit += int((number[i] - '0') * pow(10, length - 1 - i));
    }

    digit += number[length - 1] - '0';

    return digit;
}

void command_line_parser::print_help()
{
    printf(
        "RIFT Renderer version %s\n\n"
        "Options:\n\n"
        "   --threads: Number of rendering threads.  Defaults to system max if "
        "not specified\n"
        "   --samples: Number of rendering samples.  This will be split "
        "amongst "
        "the available threads\n"
        "   --resolution: Resolution of the render in width and height\n"
        "   --filepath: Output filepath for the rendered image.  The extension "
        "type will be automatically added\n"
        "   --writer: Image writer for renders, options are open_exr, png or "
        "jpeg\n",
        VERSION_STRING);

    exit(EXIT_SUCCESS);
}
