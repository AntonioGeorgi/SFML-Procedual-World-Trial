#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/Graphics.hpp>
#include <vector>

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
#endif