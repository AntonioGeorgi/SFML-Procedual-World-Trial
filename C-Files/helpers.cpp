#include "..\Headers\helpers.h"

void Backround::update(std::vector<tile> tiles) {    
    //get the width
    unsigned short width = tiles.size()/height;

    //set nummber of vertices in array (6 per tile)
    array_vertices.resize(tiles.size() * height * 6);

    //loop through all tiles
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j) {
            // get a pointer to the triangles vertices of the current tile
            sf::Vertex* triangles = &array_vertices[(i + j * width) * 6];

            // set the positions of the 6 corners of the triangles
            triangles[0].position = sf::Vector2f(i * tile_size, j * tile_size);
            triangles[1].position = sf::Vector2f((i + 1) * tile_size, j * tile_size);
            triangles[2].position = sf::Vector2f(i * tile_size, (j + 1) * tile_size);
            triangles[3].position = sf::Vector2f(i * tile_size, (j + 1) * tile_size);
            triangles[4].position = sf::Vector2f((i + 1) * tile_size, j * tile_size);
            triangles[5].position = sf::Vector2f((i + 1) * tile_size, (j + 1) * tile_size);

            // set color rgb values depending on the tiles stats
            for (size_t i = 0; i < 6; i++)
            {
                triangles[i].color.r = show_tempature * tiles[j * width + i].tempature;
                triangles[i].color.g = show_height * tiles[j * width + i].height;
                triangles[i].color.b = show_humidity * tiles[j * width + i].humidity;
            }
        }   
}

void Backround::update(std::vector<tile> tiles, unsigned short new_height, unsigned short new_tile_size) {
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
    target.draw(array_vertices, states);
}