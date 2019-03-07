#pragma once

#include "core/image_writers/ioutput_writer.h"

class jpeg_writer
  : public ioutput_writer
{
  public:
    void write(
        const float*    buffer,
        const char*     filename,
        int             size_x,
        int             size_y) const override;
};
