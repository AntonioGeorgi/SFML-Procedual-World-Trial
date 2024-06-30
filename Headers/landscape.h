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
class landscape : terrain
{
private:
    terrain_height height_map;
    landscape_parameters parameters;
    // overrides the generate terrain with a function that creates a height_map
    void generateTerrain() override;

public:
    landscape();
    // converts the landscape_parameters into perlin_parameters and whatever else is needed to create the height_map
    void init_landscape(world_size world_size ,siv::PerlinNoise::seed_type seed, landscape_parameters parameters);
    void setParameters(landscape_parameters parameters);
    // creates a new seed for the landscape
    void remakeLandscape(); // maybe I should put the seed into landscape_parameters
    landscape_parameters getParameters();
    terrain_height getHeightMap(); 
};