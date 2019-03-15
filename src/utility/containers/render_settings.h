#pragma once

#include "core/image_writers/ioutput_writer.h"
#include "core/lighting_integrators/ilight_integrator.h"
#include "core/samplers/igenerator.h"

#include <thread>

struct render_settings
{
    const int                 resolution_x;
    const int                 resolution_y;
    const int                 samples;
    const lighting_integrator light_integrator;
    const int                 threads;
    const samplers            sampler;
    const output_writers      output_writer;
    const std::string         filepath;
    const bool                use_important_sampling;
};
