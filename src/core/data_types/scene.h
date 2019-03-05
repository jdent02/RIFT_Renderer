#pragma once

#include "core/bases/icamera.h"
#include "core/bases/hitable.h"


struct scene
{
    icamera* cam;
    hitable* world;
};