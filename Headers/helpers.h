#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/Graphics.hpp>
#include <vector>

//Perlin-----------------
#include "Resources/PerlinNoise.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
//----------------------

struct Tile
{
    unsigned short height;
    unsigned short tempature;
    unsigned short humidity;
};

class Backround : public sf::Drawable, public sf::Transformable
    /* 
    Backround sets the color depending on the inputed tiles stats, 
    at the moment can only show tile stats from 0 till 255
    */
{
public:
	bool show_height 	= 1;
	bool show_tempature = 1;
	bool show_humidity	= 1;
	
	Backround(unsigned short start_height, unsigned short start_tile_size);
	void update(std::vector<Tile> tiles);
    void update(std::vector<Tile> tiles, unsigned short new_height, unsigned short new_tile_size);

private:
	unsigned short height;
	unsigned short tile_size;
	std::vector<sf::VertexArray> pseudo_quads;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

siv::PerlinNoise::seed_type seed = 623;

siv::PerlinNoise perlin{ seed };

sf::Sprite generatePerlin(sf::Texture& texture, double octaves, double persistance, unsigned int width, unsigned int height) {
    double x = 0;
    double y = 42;
    double z = 0;
    double noise;
    double a;
    sf::Color color;

    sf::Image image;
    image.create(width, height, sf::Color::Red);

    double xLim = width;
    double yLim = height;

    for (x = 0; x < xLim; x++) {
        for (z = 0; z < yLim; z++) {

            noise = perlin.octave2D_01((x / 1000.0), (z / 1000.0), octaves, persistance);
            if (noise < 0.35) {
                noise = 0.0;
                color = sf::Color::Blue;
            }
            else if (noise >= 0.35 && noise < 0.45) {
                noise = 0.2;
                color = sf::Color::Blue;
            }
            else if (noise >= 0.45 && noise < 0.55) {
                noise = 0.4;
                color = sf::Color::Yellow;
            }
            else if (noise >= 0.55 && noise < 0.65) {
                noise = 0.6;
                color = sf::Color::Green;
            }
            else if (noise >= 0.65 && noise < 0.75) {
                noise = 0.8;
                color = sf::Color::Green;
            }
            else if (noise >= 0.75 && noise < 0.79) {
                noise = 1;
                color = sf::Color(169, 169, 169);
            }
            else if (noise >= 0.79) {
                color = sf::Color::White;
            }

            a = (noise) * 255;
            //color.a = a;
            //color = sf::Color(255, 255, 255, a);
            image.setPixel(x, z, color);
        }
    }

    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);

    return sprite;
}

int random(int start, int fin) {
    return rand() % fin + start;
}

#endif