#include "png_writer.h"

#include "third_party/stb_image_write.h"

#include <cmath>
#include <iostream>

void png_writer::write(
    const float* buffer,
    const char*  filename,
    const int    size_x,
    const int    size_y) const
{
    std::cout << "Writing Output" << std::endl;

    const int buffer_size{size_x * size_y * 3};

    auto* out_buffer = new unsigned char[buffer_size];

    for (int i = 0; i < buffer_size; i++)
    {
        out_buffer[i] =
            static_cast<unsigned char>(int(255 * std::sqrt(buffer[i])));
    }

    const int success =
        stbi_write_png(filename, size_x, size_y, 3, out_buffer, size_x * 3);

    if (success != 0)
    {
        std::cout << "Done Writing Output" << std::endl;
    }
    else
    {
        std::cout << "Image Write Failed" << std::endl;
    }

    delete[] out_buffer;
}
