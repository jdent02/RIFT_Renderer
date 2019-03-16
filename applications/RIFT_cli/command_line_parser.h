#pragma once

#include "utility/containers/render_settings.h"

class command_line_parser
{
  public:
    command_line_parser() = default;

    int convert_number(size_t& length, const char* number);

    void print_help();

    RenderSettings parse(int argc, char* argv[]);
};
