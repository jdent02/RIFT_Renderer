#include "jpeg_writer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include <iostream>
#include <cmath>

void jpeg_writer::write(
    const float* buffer,
    const char* filename,
    int size_x,
    int size_y) const
{
    std::cout << "Writing Output" << std::endl;

    int buffer_size{size_x * size_y * 3};

    auto* out_buffer = new unsigned char[buffer_size];

    for (size_t i = 0; i < buffer_size; i++)
    {
        out_buffer[i] = static_cast<unsigned char>(int(255 * std::sqrt(buffer[i])));
    }

    int success = stbi_write_jpg(filename, size_x, size_y, 3, out_buffer, 90);

    if (success != 0)
    {
        std::cout << "Done Writing Output" << std::endl;
    }
    else
    {
        std::cout << "Image Write Failed" << std::endl;
    }
}