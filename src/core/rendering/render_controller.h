#pragma once

#include "core/bases/icamera.h"
#include "core/data_types/scene.h"
#include "core/image_writers/ioutput_writer.h"
#include "utility/containers/render_settings.h"
#include "utility/rng/igenerator.h"

// Forward declarations
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
            buffer_,
            settings_.filepath,
            settings_.resolution_x,
            settings_.resolution_y);
    }

    void cleanup() const;

  private:
    float*                buffer_;
    const float           inv_ns_;
    scene*                render_scene_;
    igenerator*           random_generator_{};
    std::unique_ptr<ioutput_writer>       image_writer_;
    const render_settings settings_;
};
