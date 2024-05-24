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

sf::Sprite generatePerlin(siv::PerlinNoise& perlin, sf::Texture& texture, double octaves, double persistance, unsigned int width, unsigned int height) {
    double x = 0;
    double y = 0;
    double noise;
    double a;
    sf::Color color;

    sf::Image image;
    image.create(width, height, sf::Color::Red);

    double xLim = width;
    double yLim = height;

    for (x = 0; x < xLim; x++) {
        for (y = 0; y < yLim; y++) {

            noise = perlin.octave2D_01((x / width), (y / height), octaves, persistance);
            if (noise < 0.35) {
                noise = 0.0;
                color = sf::Color::Blue;
            }
            else if (noise >= 0.35 && noise < 0.5) {
                noise = 0.2;
                color = sf::Color::Blue;
            }
            else if (noise >= 0.5 && noise < 0.55) {
                noise = 0.4;
                color = sf::Color::Yellow;
            }
            else if (noise >= 0.55 && noise < 0.65) {
                noise = 0.6;
                color = sf::Color::Green;
            }
            else if (noise >= 0.65 && noise < 0.70) {
                noise = 0.8;
                color = sf::Color::Green;
            }
            else if (noise >= 0.70 && noise < 0.75) {
                noise = 1;
                color = sf::Color(169, 169, 169);
            }
            else if (noise >= 0.75) {
                color = sf::Color::White;
            }

            a = (noise) * 255;
            //color.a = a;
            //color = sf::Color(255, 255, 255, a);
            image.setPixel(x, y, color);
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