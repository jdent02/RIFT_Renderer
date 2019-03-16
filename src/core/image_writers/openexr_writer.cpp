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
