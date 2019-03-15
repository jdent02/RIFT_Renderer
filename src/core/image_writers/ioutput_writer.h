#pragma once

#include <string>

#ifdef RIFT_USE_OPENEXR
enum output_writers
{
    JPEG,
    PNG,
    OPENEXR
};
#else
enum output_writers
{
    JPEG,
    PNG,
};
#endif // RIFT_USE_OPENEXR

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
