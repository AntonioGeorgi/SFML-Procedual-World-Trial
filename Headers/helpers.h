#ifndef HELPERS_H
#define HELPERS_H

#include <SFML/Graphics.hpp>
#include <vector>

struct tile
{
    unsigned short height;
    unsigned short tempature;
    unsigned short humidity;
};

class Backround : public sf::Drawable, public sf::Transformable
    /* 
    Backround sets the color depending on the inputed tiles stats, 
    at the moment can only show tile stats from 0 till 256S
    */
{
public:
	bool show_height 	= 1;
	bool show_tempature = 1;
	bool show_humidity	= 1;
	
	Backround(unsigned short height, unsigned short tile_size);

private:
	unsigned short tile_size;
	unsigned short height;

	sf::VertexArray array_vertices;
	void update(std::vector<tile> tiles);
    void update(std::vector<tile> tiles, unsigned short new_height, unsigned short new_tile_size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif