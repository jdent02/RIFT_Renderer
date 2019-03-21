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

#include "oiio_writer.h"

#include "OpenImageIO/imageio.h"

#include <half.h>

using namespace OpenImageIO_v2_0;

void OIIOWriter::write(
    const float*       buffer,
    const std::string& filename,
    int                size_x,
    int                size_y) const
{
    std::string out_filename = filename + ".png";
    const int   xres = 640;
    const int   yres = 640;

    // half* pixels = new half[xres * yres * 3];

    // for (int i = 0; i < xres * yres * 3; i++)
    // {
    //     pixels[i] = static_cast<half>(buffer[i]);
    // }
    int buffer_size = xres * yres * 3;

    auto* pixels = new unsigned char[buffer_size];

    for (int i = 0; i < buffer_size; i++)
    {
        pixels[i] =
            static_cast<unsigned char>(int(255 * std::sqrt(buffer[i])));
    }

    std::unique_ptr<ImageOutput> out = ImageOutput::create(out_filename);
    if (out == nullptr)
    {
        return;
    }

    ImageSpec spec(xres, yres, 3, TypeDesc::UINT8);
    out->open(out_filename, spec);
    out->write_image(TypeDesc::UINT8, pixels);

    out->close();
}
