#pragma once

#include "core/bases/icamera.h"
#include "core/image_writers/iimage_writer.h"
#include "utility/rng/igenerator.h"

#include <vector>


// Forward declarations
class camera;
class hitable;

class render_controller
{
public:
    render_controller(
            const char* filename,
            int nx,
            int ny,
            int ns,
            icamera* cam,
            hitable* world);

    ~render_controller();

    void do_render();

    void write_output() { image_writer->write(buffer, out_filename, nx, ny);}

    void cleanup();

private:
    float* buffer;
    const int nx;
    const int ny;
    const int ns;
    const float inv_nx;
    const float inv_ny;
    const float inv_ns;
    icamera* cam;
    hitable* world;
    igenerator* random_generator;
    iimage_writer* image_writer;
    const char* out_filename;
};
