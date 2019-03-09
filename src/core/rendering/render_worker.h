#pragma once

#include "utility/rng/igenerator.h"

#include <memory>

struct render_settings;
struct scene;
class icamera;
class ihitable;

namespace render_worker
{
void run_thread(
    int                    seed,
    int                    ns,
    float*                 buffer,
    const scene&           render_scene,
    const render_settings& settings);

std::unique_ptr<igenerator> set_generator(
    const render_settings& settings,
    const int&             seed);

} // namespace render_worker
