#pragma once

// #include <SFML/Graphics.hpp>
// #include <vector>
#include <math.h>

struct perlin_parameters {
    int seed;
    double octaves;
    double persistence;

    perlin_parameters& operator=(const landscape_parameters& lp) {
        seed = lp.origin;
        octaves = lp.height;
        persistence = lp.low;
        return *this;
    }
};

struct landscape_parameters {
    int origin;
    double height;
    double low;
    float water_level;
};

struct terrain_height
{
    /* data */
};
struct world_size
{
    unsigned int x;
    unsigned int y;
};

int random(int start, int fin);

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

