#pragma once

#include "helpers.h"
#include "../Resources/PerlinNoise.hpp"
/*
The general class from which all terrain related once inherit.
*/
class terrain
{
private:
    world_size size;
    siv::PerlinNoise::seed_type seed; // maybe seed should go to parameters_perlin
    perlin_parameters parameters_perlin;
    siv::PerlinNoise perlin;
    // generates the perlin
    void generatePerlin();
    virtual void generateTerrain();
    
public:
    terrain(/* args */);
    virtual ~terrain();
    // takes the starting parameters and calls generate function
    void init_terrain (world_size world_size ,siv::PerlinNoise::seed_type seed, perlin_parameters parameters_perlin); 
    // take the new seed and call generateTerrain
    void reseed(siv::PerlinNoise::seed_type seed = random(0, 9999999)); 
    // take the new parameter and call generateTerrain
    void setPerlinParameter(perlin_parameters parameters); 
    perlin_parameters getParameters();
    siv::PerlinNoise::seed_type getSeed();

};
