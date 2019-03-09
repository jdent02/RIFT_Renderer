#include "png_writer.h"

#include "third_party/stb_image_write.h"

#include <cmath>
#include <iostream>

void png_writer::write(
    const float*       buffer,
    const std::string& filename,
    const int          size_x,
    const int          size_y) const
{
    std::cout << "Writing Output\n";

    const int buffer_size{size_x * size_y * 3};

    auto* out_buffer = new unsigned char[buffer_size];

    std::string out_filename = filename + ".png";

    for (int i = 0; i < buffer_size; i++)
    {
        out_buffer[i] =
            static_cast<unsigned char>(int(255 * std::sqrt(buffer[i])));
    }

    const int success = stbi_write_png(
        out_filename.c_str(), size_x, size_y, 3, out_buffer, size_x * 3);

    if (success != 0)
    {
        std::cout << "Done Writing Output\n";
    }
    else
    {
        std::cout << "Image Write Failed\n";
    }

    delete[] out_buffer;
}
