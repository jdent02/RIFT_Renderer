#pragma once

class icamera;
class ihitable;

struct scene
{
    icamera*  cam;
    ihitable* world;
};
