#ifndef RENDER_H
#define RENDER_H

#include "hitables/hitable.h"
#include "camera/camera.h"

#include <memory>
#include <vector>


class renderer
{
public:
    renderer(
        const int nx,
        const int ny,
        const int ns,
        camera cam,
        hitable *world);

    ~renderer() = default;

    void do_render() const;
    void write_buffer() const;

private:
    std::unique_ptr<std::vector<std::vector<int>>> buffer;
    const int nx;
    const int ny;
    const int ns;
    const float inv_nx;
    const float inv_ny;
    camera cam;
    hitable *world;
};


#endif // RENDER_H
