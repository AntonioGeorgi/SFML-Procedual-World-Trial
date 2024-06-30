#pragma once

#include "landscape.h"
#include "weather.h"

class world
{
private:
    landscape world_landscape;
    weather world_weather();
public:
    world();
    ~world();
};
