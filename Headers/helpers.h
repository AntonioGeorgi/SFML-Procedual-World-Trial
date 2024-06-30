#pragma once

// #include <SFML/Graphics.hpp>
// #include <vector>

#include "../Resources/PerlinNoise.hpp"
struct perlin_parameters 
{
    siv::PerlinNoise::seed_type seed;
    int32_t octaves;
    float persistence;
};

struct landscape_parameters : perlin_parameters
{
    float water_level; // does probably fit better into hydrology or something like that
};

struct terrain_height
{
    /* data */
};
struct world_size
{
    float x;
    float y;
};

#include <math.h>
int random(int start, int fin);

    // perlin_parameters& operator=(const landscape_parameters& lp) {
    //     seed = lp.seed;
    //     octaves = lp.complexity;
    //     persistence = lp.detail;
    //     return *this;
    // }

//Perlin-----------------
// #include "../Resources/PerlinNoise.hpp"
// #include <string>
// #include <iostream>
// #include <fstream>
// #include <set>
// #include <iterator>
// #include <stdlib.h>
// #include <stdio.h>
//----------------------

// struct Tile
// {
//     float height;
//     float temperature;
//     float humidity;
// 	float sky_wind[8]; //sky wind moves from warm to cold while ground_wind moves from cold to hot
// }; 

//sf::Sprite generatePerlin(siv::PerlinNoise& perlin, sf::Texture& texture, double octaves, double persistance, unsigned int width, unsigned int height);
// void generatePerlinTexture(siv::PerlinNoise& perlin, sf::Texture& texture, std::vector<Tile>& tiles, double octaves, double persistance, unsigned int width, unsigned int height, sf::Color color = sf::Color::White);
// void updateTexture(sf::Texture& texture, std::vector<Tile> tiles, unsigned int width, unsigned int height, sf::Color color = sf::Color::White);

// void setWind(std::vector<Tile>& tiles, unsigned int width, unsigned int height);
// void executeWind(std::vector<Tile>& tiles, float wind_impact, unsigned int width, unsigned int height);
// // void printWind(std::vector<Tile> tiles, unsigned int visibility_limit, unsigned int width, unsigned int height);
// void printTemperature(std::vector<Tile> tiles, std::ofstream& outFile, unsigned int width, unsigned int height, bool sum_only);

