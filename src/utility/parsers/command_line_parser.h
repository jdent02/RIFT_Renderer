#pragma once

#include "utility/containers/render_settings.h"

inline int convert_number(size_t& length, const char* number)
{
    int digit{0};

    for (size_t i = 0; i < length - 1; i++)
    {
        digit += int((number[i] - '0') * pow(10, length - 1 - i));
    }

    digit += number[length - 1] - '0';

    return digit;
}

class command_line_parser
{
  public:
    render_settings parse(const int argc, char* argv[]);
};
