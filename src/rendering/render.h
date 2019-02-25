#ifndef RENDER_H
#define RENDER_H

#include "hitables/hitable.h"
#include "camera/camera.h"

#include <vector>


class renderer
{
public:
    renderer() = default;
    ~renderer() = default;
    void do_render(
        std::vector<std::vector<int>> &buffer,
        const int nx,
        const int ny,
        const int ns,
        const float inv_nx,
        const float inv_ny,
        camera cam,
        hitable *world) const;

    void write_buffer(
        std::vector<std::vector<int>>& buffer,
        const int& x_res,
        const int& y_res);
};


#endif // RENDER_H
