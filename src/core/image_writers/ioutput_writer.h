#pragma once

class ioutput_writer
{
  public:
    virtual ~ioutput_writer() = default;

    virtual void write(
        const float* buffer,
        const char*  filename,
        int          size_x,
        int          size_y) const = 0;
};
