
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/helpers.h"

const int TILE_SIZE   = 1;
const int GRID_WIDTH  = 120 * 1;
const int GRID_HEIGHT = 120 * 1;

int main()
{
    siv::PerlinNoise::seed_type seed = random(0, 9999999);
    siv::PerlinNoise perlin{ seed };

    // create the window
    sf::RenderWindow window(sf::VideoMode(GRID_WIDTH, GRID_HEIGHT), "SFML Prodcedual World Trial!");

    sf::CircleShape shape(TILE_SIZE / 2);
    shape.setFillColor(sf::Color::Magenta);

    //Perlin noise Sprite-------------------------------------------------
    bool height = false, humidity = false, temperature = true;
    double octaves = 9, percistance = 0.6, step = 0.1;

    std::vector<Tile> tiles(GRID_WIDTH * GRID_HEIGHT);
    sf::Texture height_texture;
    sf::Texture humidity_texture;
    sf::Texture temperature_texture;

    //sf::Sprite perlinSprite = generatePerlin(perlin, texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
    generatePerlinTexture(perlin, height_texture, tiles, octaves, percistance, GRID_WIDTH, GRID_HEIGHT, sf::Color::Green);
    sf::Sprite perlin_height_sprite(height_texture);
    seed = random(0, 9999999);
    perlin.reseed(seed);
    generatePerlinTexture(perlin, humidity_texture, tiles, octaves, percistance, GRID_WIDTH, GRID_HEIGHT, sf::Color::Blue);
    sf::Sprite perlin_humidity_sprite(humidity_texture);
    seed = random(0, 9999999);
    perlin.reseed(seed);
    generatePerlinTexture(perlin, temperature_texture, tiles, octaves, percistance, GRID_WIDTH, GRID_HEIGHT, sf::Color::Red);
    sf::Sprite perlin_temperature_sprite(temperature_texture);
    //----------------------------------------------------------------

    // run the program as long as the window is open
    while (window.isOpen()) {
                
        // // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
            // "close requested" event: we close the window
            case sf::Event::Closed:
                window.close();
                break;

            // key pressed
            case sf::Event::KeyPressed:
                //is triggered as long as key is pressed, but with default operating system delay
                //use bool for smooth triggering 
                //repeat can be disabled with: window.setKeyRepeatEnabled(false)
                break;

            case sf::Event::KeyReleased:
                switch (event.key.scancode)
                {
                case sf::Keyboard::A:
                    octaves -= step;
                    // perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;

                case sf::Keyboard::Q:
                    //height = !height;
                    setWind(tiles, GRID_WIDTH, GRID_HEIGHT);
                    printWind(tiles, 3, GRID_WIDTH, GRID_HEIGHT);
                    //executeWind(tiles, 0.7, GRID_WIDTH, GRID_HEIGHT);

                    updateTexture(temperature_texture, tiles, GRID_WIDTH, GRID_HEIGHT, sf::Color::Red);
                    break;

                case sf::Keyboard::W:
                    //humidity = !humidity;
                    break;
                
                case sf::Keyboard::E:
                    temperature = !temperature;
                    break;

                case sf::Keyboard::D:
                    octaves += step;
                    // perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;

                case sf::Keyboard::R:
                    seed = random(0, 9999999);
                    perlin.reseed(seed);
                    // perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;
                
                case sf::Keyboard::P:
                    step += 0.01;
                    break;

                case sf::Keyboard::M:
                    step -= 0.01;
                    break;

                case sf::Keyboard::Z:
                    percistance -= step;
                    // perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;

                case sf::Keyboard::C:
                    percistance += step;
                    // perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;

                default:
                    break;
                }
                break;

            case sf::Event::Resized:
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
                break;
                // we don't process other types of events
            default:
                break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        //window.draw(backround);
        // window.draw(shape);
        if (height == true)      {window.draw(perlin_height_sprite);}
        if (humidity == true)    {window.draw(perlin_humidity_sprite);}
        if (temperature == true) {window.draw(perlin_temperature_sprite);}


        // end the current frame
        window.display();
    }

    return 0;
}