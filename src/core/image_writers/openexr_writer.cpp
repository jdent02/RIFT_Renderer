#include "openexr_writer.h"

#include "OpenEXR/ImfRgbaFile.h"

#include <cstdio>

using namespace Imf_2_2;

void openexr_writer::write(
    const float*       buffer,
    const std::string& filename,
    int                size_x,
    int                size_y) const
{
    printf("Writing Output EXR");
    std::string out_filename = filename + ".exr";
    const int   pixel_count{size_x * size_y};
    Rgba*       out_buffer = new Rgba[pixel_count];

    int buffer_index{0};
    for (int i = 0; i < pixel_count; i++)
    {
        Rgba temp;

        temp.r = buffer[buffer_index++];
        temp.g = buffer[buffer_index++];
        temp.b = buffer[buffer_index++];
        temp.a = 1.f;

        out_buffer[i] = temp;
    }

    RgbaOutputFile file(out_filename.c_str(), size_x, size_y, WRITE_RGBA);
    file.setFrameBuffer(out_buffer, 1, size_x);
    file.writePixels(size_y);

    printf("File written");
}
