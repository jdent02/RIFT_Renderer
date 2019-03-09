#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "core/image_writers/ioutput_writer.h"

#include <string>

class jpeg_writer : public ioutput_writer
{
  public:
    void write(
        const float*       buffer,
        const std::string& filename,
        int                size_x,
        int                size_y) const override;
};
