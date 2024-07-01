#pragma once

#include "helpers.h"
#include "terrain.h"
#include "../Resources/PerlinNoise.hpp"
/*
The landscape is the backbone of any world.
It's defines the valleys and mountains, that in turn influence weather, vegetation, etc.

For now it will be just perlin noise.
The settings for the noise are what defines the terrain.

I may later add other fancy algorithm to improve the terrain but for now I am too lazy.

*/
class landscape : terrain<landscape_parameters>
{
private:
    terrain_height height_map;
    landscape_parameters parameters;
    // overrides the generate terrain with a function that creates a height_map
    void generateTerrain() override;

public:
    landscape();
    // gives a struct containing the height of each cell of the world
    terrain_height getHeightMap(); 
};