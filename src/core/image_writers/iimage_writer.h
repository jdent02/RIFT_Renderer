#pragma once


class iimage_writer
{
  public:
    virtual ~iimage_writer() = default;
    virtual void write(
        const float* buffer,
        const char* filename,
        int size_x,
        int size_y) const = 0;
};
