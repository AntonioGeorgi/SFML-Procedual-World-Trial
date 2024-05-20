#include "..\Headers\helpers.h"


void Backround::update(std::vector<tile> tiles, unsigned short new_height = height, unsigned short new_tile_size = tile_size) {

    if ((new_height != height) || (new_tile_size != tile_size))
    {
        height      = new_height;
        tile_size   = new_tile_size;
    }
    
    //get the width
    unsigned short width = tiles.size/new_height;

    //set nummber of vertices in array (6 per tile)
    array_vertices.resize(tiles.size * height * 6);

    //loop through all tiles
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j) {
            //get the current tile_type
            int tile_type = tile_grid[i + j * width].state;

            // get a pointer to the triangles vertices of the current tile
            sf::Vertex* triangles = &array_vertices[(i + j * width) * 6];

            // set the positions of the 6 corners of the triangles
            triangles[0].position = sf::Vector2f(i * tile_size, j * tile_size);
            triangles[1].position = sf::Vector2f((i + 1) * tile_size, j * tile_size);
            triangles[2].position = sf::Vector2f(i * tile_size, (j + 1) * tile_size);
            triangles[3].position = sf::Vector2f(i * tile_size, (j + 1) * tile_size);
            triangles[4].position = sf::Vector2f((i + 1) * tile_size, j * tile_size);
            triangles[5].position = sf::Vector2f((i + 1) * tile_size, (j + 1) * tile_size);

            // set matching coordinates in tilemap_texture
            triangles[0].texCoords = sf::Vector2f(tile_position_width * tile_size, tile_position_height * tile_size);
            triangles[1].texCoords = sf::Vector2f((tile_position_width + 1) * tile_size, tile_position_height * tile_size);
            triangles[2].texCoords = sf::Vector2f(tile_position_width * tile_size, (tile_position_height + 1) * tile_size);
            triangles[3].texCoords = sf::Vector2f(tile_position_width * tile_size, (tile_position_height + 1) * tile_size);
            triangles[4].texCoords = sf::Vector2f((tile_position_width + 1) * tile_size, tile_position_height * tile_size);
            triangles[5].texCoords = sf::Vector2f((tile_position_width + 1) * tile_size, (tile_position_height + 1) * tile_size);

        }
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