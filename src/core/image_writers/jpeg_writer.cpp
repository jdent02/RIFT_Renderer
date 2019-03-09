#include "jpeg_writer.h"

#include "third_party/stb_image_write.h"

#include <iostream>

void jpeg_writer::write(
    const float*       buffer,
    const std::string& filename,
    const int          size_x,
    const int          size_y) const
{
    std::cout << "Writing Output" << std::endl;

    const int buffer_size{size_x * size_y * 3};

    std::string out_filename = filename + ".jpg";

    auto* out_buffer = new unsigned char[buffer_size];

    for (int i = 0; i < buffer_size; i++)
    {
        out_buffer[i] =
            static_cast<unsigned char>(int(255 * std::sqrt(buffer[i])));
    }

    const int success =
        stbi_write_jpg(out_filename.c_str(), size_x, size_y, 3, out_buffer, 90);

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
