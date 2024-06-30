#pragma once

#include "helpers.h"
#include "../Resources/PerlinNoise.hpp"
/*
The general class from which all terrain related once inherit.
terrain_parameters should inherit from perlin_parameters
*/
template <typename terrain_parameters>
class terrain
{
private:
    world_size size;
    terrain_parameters parameters;
    siv::PerlinNoise perlin;
    // generates the perlin
    float givePerlinNoise(float x, float y);
    virtual void generateTerrain() = 0;
    
public:
    terrain(/* args */);
    virtual ~terrain();
    // takes the starting parameters and calls generateTerrain
    void init_terrain (world_size size, terrain_parameters parameters); 
    // take the new seed and call generateTerrain
    void reseed(siv::PerlinNoise::seed_type seed = random(0, 9999999)); 
    // take the new parameter and call generateTerrain
    void setParameter(terrain_parameters parameters); 
    terrain_parameters getParameters();
    siv::PerlinNoise::seed_type getSeed();

};
