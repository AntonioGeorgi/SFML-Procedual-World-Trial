#pragma once

#include "helpers.h"
#include "../Resources/PerlinNoise.hpp"
/*
This class will take care of all things water. (At least close to the ground.)
The water can also be replaced if other substances that act like water on earth.

Here is where the water level for oceans will be created, rivers be carved, glaciers be formed, etc.
It will not create rain but influence the humidity of a region. (Water evaporates above bodies of water.)
*/
class hydrology
{
private:
    world_size size;
    humidity_map humidity;
    siv::PerlinNoise::seed_type seed;
    perlin_parameters parameters;
public:
    hydrology(/* args */);
    ~hydrology();
};