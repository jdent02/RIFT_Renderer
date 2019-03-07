#pragma once

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
    icamera*  cam,
    ihitable* world);

} // namespace render_worker
