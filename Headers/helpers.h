#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

//Perlin-----------------
#include "../Resources/PerlinNoise.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//----------------------

struct Tile
{
    float height;
    float tempature;
    float humidity;
	sf::Vector2f sky_wind; //sky wind moves from warm to cold while ground_wind moves from cold to hot
}; 

//sf::Sprite generatePerlin(siv::PerlinNoise& perlin, sf::Texture& texture, double octaves, double persistance, unsigned int width, unsigned int height);
void generatePerlinTexture(siv::PerlinNoise& perlin, sf::Texture& texture, std::vector<Tile>& tiles, double octaves, double persistance, unsigned int width, unsigned int height, sf::Color color = sf::Color::White);
void updateTexture(sf::Texture& texture, std::vector<Tile> tiles, unsigned int width, unsigned int height, sf::Color color = sf::Color::White);

void setWind(std::vector<Tile>& tiles, unsigned int width, unsigned int height);
void executeWind(std::vector<Tile>& tiles, float wind_impact, unsigned int width, unsigned int height);
void printWind(std::vector<Tile> tiles, unsigned int visibility_limit, unsigned int width, unsigned int height);

int random(int start, int fin);
