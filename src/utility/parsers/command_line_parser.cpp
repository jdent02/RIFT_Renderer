#include "command_line_parser.h"

#include "core/image_writers/ioutput_writer.h"
#include "utility/containers/render_settings.h"
#include "utility/rng/igenerator.h"

#include <cstdio>
#include <iostream>
#include <thread>

render_settings command_line_parser::parse(const int argc, char* argv[])
{
    int temp_threads{static_cast<int>(std::thread::hardware_concurrency())};
    samplers       sampler{XORO_128};
    int            x_res{1920};
    int            y_res{1080};
    output_writers out_writer{PNG};
    int            samples{100};
    bool           use_importance_sampling{true};
    std::string    filepath{};

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
                           temp_threads,
                           sampler,
                           out_writer,
                           filepath,
                           use_importance_sampling};
}
