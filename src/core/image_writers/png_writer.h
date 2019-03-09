#pragma once

#include "core/image_writers/ioutput_writer.h"

#include <string>

class png_writer : public ioutput_writer
{
  public:
    void write(
        const float*       buffer,
        const std::string& filename,
        int                size_x,
        int                size_y) const override;
};
