#pragma once

struct render_settings;
struct scene;
class icamera;
class ihitable;

namespace render_worker
{
void run_thread(
    float                  seed,
    int                    ns,
    float*                 buffer,
    const scene&           render_scene,
    const render_settings& settings);

} // namespace render_worker
