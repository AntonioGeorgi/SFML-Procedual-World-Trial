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
{
public:
	//Backround(unsigned short height, unsigned short tile_size);
	//unsigned short give_height();

private:
	unsigned short tile_size;
	unsigned short height;

	sf::VertexArray array_vertices;
	
    void update(std::vector<tile> tiles, unsigned short new_height = height, unsigned short new_tile_size = tile_size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif