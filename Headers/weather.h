#pragma once

#include "helpers.h"

/*
This class is supposed to be an importable weather component for a world of given size.
The weather shall first get a Landscape bringing with it a world size and certain special terrains (mounts, valleys...).

*/
class weather
{
private:
    world_size size; 
    height_map height;
    float water_level; // maybe I should but this into landscape???
public:
    weather();
    ~weather();
};