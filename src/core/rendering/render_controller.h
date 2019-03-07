#pragma once

#include "core/bases/icamera.h"
#include "core/image_writers/ioutput_writer.h"
#include "utility/rng/igenerator.h"

// Forward declarations
class camera;

class ihitable;

class render_controller
{
  public:
    render_controller(
        const char* filename,
        int         nx,
        int         ny,
        int         ns,
        icamera*    cam,
        ihitable*   world);

    ~render_controller() = default;

    void do_render();

    void write_output() const
    {
        image_writer_->write(buffer_, out_filename_, nx_, ny_);
    }

    void cleanup() const;

  private:
    float*          buffer_;
    const int       nx_;
    const int       ny_;
    const int       ns_;
    const float     inv_ns_;
    icamera*        cam_;
    ihitable*       world_;
    igenerator*     random_generator_{};
    ioutput_writer* image_writer_;
    const char*     out_filename_;
};
