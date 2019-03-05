#pragma once

#include "iimage_writer.h"


class jpeg_writer
    :public iimage_writer
{
  public:
    virtual void write(
        const float* buffer,
        const char* filename,
        int size_x,
        int size_y) const override;

};
