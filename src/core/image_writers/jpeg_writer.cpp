// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
