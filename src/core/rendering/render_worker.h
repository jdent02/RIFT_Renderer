#pragma once

struct scene;
class icamera;
class ihitable;

namespace render_worker
{
void run_thread(
    int       seed,
    int       nx,
    int       ny,
    int       ns,
    float*    buffer,
    scene* render_scene);

} // namespace render_worker
