#pragma once


// Forward declarations
class camera;
class hitable;

class renderer
{
public:
    renderer(
        int nx,
        int ny,
        int ns,
        camera* cam,
        hitable* world);

    ~renderer() = default;

    void do_render() const;

    void write_JPEG() const;

private:
    float* buffer;
    const int nx;
    const int ny;
    const int ns;
    const float inv_nx;
    const float inv_ny;
    const float inv_ns;
    camera* cam;
    hitable* world;
};
