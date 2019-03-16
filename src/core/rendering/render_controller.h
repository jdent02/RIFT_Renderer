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

#pragma once

#include "core/image_writers/i_out_writer.h"
#include "core/samplers/rng/i_rand_generator.h"
#include "utility/containers/render_settings.h"
#include "utility/containers/scene.h"

#include <memory>

class RenderController
{
  public:
    RenderController(const RenderSettings& settings, const Scene* render_scene);

    ~RenderController() = default;

    void do_render();

    void write_output() const
    {
        m_image_writer->write(
            m_buffer.get(),
            m_settings.m_filepath,
            m_settings.m_resolution_x,
            m_settings.m_resolution_y);
    }

  private:
    std::unique_ptr<float[]>        m_buffer;
    const float                     m_inv_ns;
    const Scene*                    m_render_scene;
    std::unique_ptr<IRandGenerator> m_random_generator{};
    std::unique_ptr<IOutWriter>     m_image_writer;
    const RenderSettings            m_settings;
};
