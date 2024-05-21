#include "..\Headers\helpers.h"

Backround::Backround(unsigned short start_height, unsigned short start_tile_size) {
    triangle_strips.resize(start_height);
    tile_size   = start_tile_size;
}

void Backround::update(std::vector<Tile> tiles) {    
    
    //get the height and width
    unsigned short height = triangle_strips.size();
    unsigned short width  = tiles.size()/height;

    //loop through all tiles
    for (int i = 0; i < height; ++i) {
        //set nummber of vertices in array (6 per tile) and set ptimitivtype to tristrip
        triangle_strips[i].setPrimitiveType(sf::TriangleStrip);
        triangle_strips[i].resize((width + 1) * 2);

        for (int j = 0; j < width + 1; ++j) {
            // get a pointer to the triangles vertices of the current tile
            sf::Vertex* triangles = &triangle_strips[i][j * 2];

            // set the positions of the 6 corners of the triangles
            triangles[0].position = sf::Vector2f(j * tile_size, i * tile_size);
            triangles[1].position = sf::Vector2f(j * tile_size, (i + 1) * tile_size);

            // set color rgb values depending on the tiles stats
            for (size_t k = 0; k < 2; k++)
            {
                triangles[k].color.r = show_tempature * tiles[j +i * width].tempature;
                triangles[k].color.g = show_height * tiles[j +i * width].height;
                triangles[k].color.b = show_humidity * tiles[j +i * width].humidity;
            }
        } 
    }
}

void Backround::update(std::vector<Tile> tiles, unsigned short new_height, unsigned short new_tile_size) {
    triangle_strips.resize(new_height);
    tile_size   = new_tile_size;
    update(tiles);
}

void Backround::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    //states.texture = &tilemap_texture;

    // draw the vertex array
    for (size_t i = 0; i < triangle_strips.size(); i++)
    {
        target.draw(triangle_strips[i], states);
    }
}