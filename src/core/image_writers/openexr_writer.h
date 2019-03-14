#pragma once

#include "ioutput_writer.h"



class openexr_writer : public ioutput_writer
{

  public:
    void write(
        const float*       buffer,
        const std::string& filename,
        int                size_x,
        int                size_y) const override;
};
