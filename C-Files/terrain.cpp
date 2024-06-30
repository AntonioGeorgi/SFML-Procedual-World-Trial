#include "..\Headers\terrain.h"
template <typename terrain_parameters>
float terrain<terrain_parameters>::givePerlinNoise(float x, float y)
{
    float noise = perlin.octave2D_01(x, y, parameters.octaves, parameters.persistence);
    return noise;
}

template <typename terrain_parameters>
void terrain<terrain_parameters>::init_terrain (world_size size, terrain_parameters parameters)
{
    this->size = size;
    this->parameters = parameters;
    generateTerrain();
}

template <typename terrain_parameters>
void terrain<terrain_parameters>::reseed(siv::PerlinNoise::seed_type seed = random(0, 9999999))
{
    this->parameters.seed = seed;
    generateTerrain();
}

template <typename terrain_parameters>
void terrain<terrain_parameters>::setParameter(terrain_parameters parameters)
{
    this->parameters = parameters;
    generateTerrain();
} 

template <typename terrain_parameters>
terrain_parameters terrain<terrain_parameters>::getParameters()
{
    return this->parameters;
}

template <typename terrain_parameters>
siv::PerlinNoise::seed_type terrain<terrain_parameters>::getSeed()
{
    return this->parameters.seed;
}