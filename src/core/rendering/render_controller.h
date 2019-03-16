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

#include "utility/containers/scene.h"
#include "core/image_writers/ioutput_writer.h"
#include "core/samplers/igenerator.h"
#include "utility/containers/render_settings.h"

#include <memory>

// Forward declarations
struct scene;
struct render_settings;
class camera;
class ihitable;

class render_controller
{
  public:
    render_controller(const render_settings& settings, scene* render_scene);

    ~render_controller() = default;

    void do_render();

    void write_output() const
    {
        image_writer_->write(
            buffer_.get(),
            settings_.filepath,
            settings_.resolution_x,
            settings_.resolution_y);
    }

  private:
    std::unique_ptr<float[]>        buffer_;
    const float                     inv_ns_;
    scene*                          render_scene_;
    std::unique_ptr<igenerator>     random_generator_{};
    std::unique_ptr<ioutput_writer> image_writer_;
    const render_settings           settings_;
};
