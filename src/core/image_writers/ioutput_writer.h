#pragma once

#include <string>

enum output_writers
{
    JPEG,
    PNG
};

class ioutput_writer
{
  public:
    virtual ~ioutput_writer() = default;

    virtual void write(
        const float*       buffer,
        const std::string& filename,
        int                size_x,
        int                size_y) const = 0;
};
