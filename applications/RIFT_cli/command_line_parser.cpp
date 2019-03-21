#include "command_line_parser.h"

#include "utility/version/version.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <thread>

RenderSettings command_line_parser::parse(const int argc, char* argv[])
{
    int         threads{static_cast<int>(std::thread::hardware_concurrency())};
    int         xres{1920};
    int         yres{1080};
    int         samples{100};
    samplers    sampler{XORO_128};
    std::string filepath{"../image_vcpp"};
    std::string integrator_string{"Path Tracer"};
    output_writers out_writer{OPENIMAGEIO};
    IntegratorEnum integrator{PATH_TRACING};

    for (int i = 0; i < argc; i++)
    {
        if (!static_cast<bool>(strcmp(argv[i], "--threads")))
        {
            char*  temp_threads = argv[i + 1];
            size_t str_len = strlen(temp_threads);
            threads = convert_number(str_len, temp_threads);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--resolution")))
        {
            char*  x = argv[i + 1];
            size_t x_len = strlen(x);
            xres = convert_number(x_len, x);
            char*  y = argv[i + 2];
            size_t y_len = strlen(y);
            yres = convert_number(y_len, y);
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--filepath")))
        {
            filepath = argv[i + 1];
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--integrator")))
        {
            if (!static_cast<bool>(strcmp(argv[i + 1], "path")))
            {
                integrator = PATH_TRACING;
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "direct")))
            {
                integrator = DIRECT_LIGHTING;
                integrator_string = "Direct Lighting";
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "importance")))
            {
                integrator = LIGHT_SAMPLE_PATH_TRACING;
                integrator_string = "Material Importance Sampling";
            }
        }
        else if (!static_cast<bool>(strcmp(argv[i], "--samples")))
        {
            char*  sample_num = argv[i + 1];
            size_t str_len = strlen(sample_num);
            samples = convert_number(str_len, sample_num);
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
#ifdef RIFT_USE_PLUGINS
            else if (!static_cast<bool>(strcmp(argv[i + 1], "open_exr")))
            {
                out_writer = OPENEXR;
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "oiio")))
            {
                out_writer = OPENIMAGEIO;
            }
#else
            else if (!static_cast<bool>(strcmp(argv[i + 1], "open_exr")))
            {
                printf("ERROR: OpenEXR writer is not available.  Please "
                       "compile RIFT with plugin support\n");
                exit(EXIT_FAILURE);
            }
            else if (!static_cast<bool>(strcmp(argv[i + 1], "oiio")))
            {
                printf("ERROR: OpenImageIO writer is not available.  Please "
                    "compile RIFT with plugin support\n");
                exit(EXIT_FAILURE);
            }
#endif
        }
    }

    printf(
        "Render Settings:\n"
        "Resolution: %i %i\n"
        "Number of Samples: %i\n"
        "Integrator: %s\n"
        "Rendering Threads: %i\n",
        xres,
        yres,
        samples,
        integrator_string.c_str(),
        threads);

    return RenderSettings{xres,
                          yres,
                          samples,
                          integrator,
                          threads,
                          sampler,
                          out_writer,
                          filepath};
}

int command_line_parser::convert_number(size_t& length, const char* number)
{
    int m_digit{0};

    for (size_t i = 0; i < length - 1; i++)
    {
        m_digit += int((number[i] - '0') * pow(10, length - 1 - i));
    }

    m_digit += number[length - 1] - '0';

    return m_digit;
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
        "   --writer: Image writer for renders, options are open_exr (if RIFT "
        "was compiled with OpenEXR support), png or "
        "jpeg\n",
        VERSION_STRING);

    exit(EXIT_SUCCESS);
}
