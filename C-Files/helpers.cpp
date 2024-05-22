#include "..\Headers\helpers.h"

Backround::Backround(unsigned short start_height, unsigned short start_tile_size) {
    height      = start_height;
    tile_size   = start_tile_size;
}

void Backround::update(std::vector<Tile> tiles) {    
    
    //get the height and width
    unsigned short width  = tiles.size()/height;
    pseudo_quads.resize(width * height);

    //loop through all tiles
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            //set nummber of vertices in array (6 per tile) and set ptimitivtype to tristrip
            pseudo_quads[i + j * height].setPrimitiveType(sf::TriangleStrip);
            pseudo_quads[i + j * height].resize(4);

            // set the positions of the 6 corners of the triangles
            pseudo_quads[i + j * height][0].position = sf::Vector2f(i * tile_size      , j * tile_size);
            pseudo_quads[i + j * height][1].position = sf::Vector2f(i * tile_size      , (j + 1) * tile_size);
            pseudo_quads[i + j * height][2].position = sf::Vector2f((i + 1) * tile_size, j * tile_size);
            pseudo_quads[i + j * height][3].position = sf::Vector2f((i + 1) * tile_size, (j + 1) * tile_size);

            // set color rgb values depending on the tiles stats
            for (size_t k = 0; k < 4; k++)
            {
                pseudo_quads[i + j * height][k].color.r = show_tempature * tiles[i +j * width].tempature;
                pseudo_quads[i + j * height][k].color.g = show_height    * tiles[i +j * width].height;
                pseudo_quads[i + j * height][k].color.b = show_humidity  * tiles[i +j * width].humidity;
            }
        } 
    }
}

void Backround::update(std::vector<Tile> tiles, unsigned short new_height, unsigned short new_tile_size) {
    height      = new_height;
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
    for (size_t i = 0; i < pseudo_quads.size(); i++)
    {
        target.draw(pseudo_quads[i], states);
    }
}