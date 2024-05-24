
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/helpers.h"

const int TILE_SIZE   = 1;
const int GRID_WIDTH  = 1000;
const int GRID_HEIGHT = 1000;

int main()
{
    siv::PerlinNoise::seed_type seed = 625;
    siv::PerlinNoise perlin{ seed };

    // create the window
    sf::RenderWindow window(sf::VideoMode(TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT), "SFML Prodcedual World Trial!");

    sf::CircleShape shape(TILE_SIZE / 2);
    shape.setFillColor(sf::Color::Magenta);

    bool height = true, humidity = true, temperature = true;
    std::cout << temperature << std::endl;

    //Perlin noise Sprite-------------------------------------------------
    double octaves = 9, percistance = 0.6, step = 0.1;

    sf::Texture height_texture;
    sf::Texture humidity_texture;
    sf::Texture temperature_texture;

    //sf::Sprite perlinSprite = generatePerlin(perlin, texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
    generatePerlinTexture(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT, sf::Color::Green);
    sf::Sprite perlin_height_sprite(height_texture);
    generatePerlinTexture(perlin, humidity_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT, sf::Color::Blue);
    sf::Sprite perlin_humidity_sprite(humidity_texture);
    generatePerlinTexture(perlin, temperature_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT, sf::Color::Red);
    sf::Sprite perlin_temperature_sprite(temperature_texture);

    srand(std::time(0));
    float dt;
    sf::Clock dt_clock;

    sf::Clock timer;

    sf::Font font;
    if (!font.loadFromFile("./Resources/arial.ttf"))
    {
        // error...
    }
    sf::Text time;
    time.setFont(font);
    time.setString("Elapsed: " + std::to_string(timer.getElapsedTime().asSeconds()));
    time.setCharacterSize(16); // in pixels, not points!
    time.setFillColor(sf::Color::Red);
    time.setPosition(10, 10);
    time.setStyle(sf::Text::Bold | sf::Text::Underlined);
    //----------------------------------------------------------------

    // for (size_t i = 0; i < tiles.size(); i++)
    // {
    //     tiles[i].height     = i / GRID_WIDTH * 255 / GRID_HEIGHT;
    //     tiles[i].humidity   = i * 10;
    //     tiles[i].temperature  = i % GRID_HEIGHT * 255 / GRID_WIDTH;
    // }
    // backround.update(tiles);
    window.setKeyRepeatEnabled(false);
    // run the program as long as the window is open
    while (window.isOpen())
    {        
        window.clear();

        time.setString("Elapsed: " + std::to_string(timer.getElapsedTime().asSeconds())
                        + "\nSeed: " + std::to_string(seed)
                        + "\nOctaves (-A\tD+): " + std::to_string(octaves)
                        + "\nPercistance/Amplitude (-Z\tC+): " + std::to_string(percistance)
                        + "\nStep (-(-)\t(=)+): " + std::to_string(step));

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            height = (height)? false : true;
            std::cout << height << std::endl;
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
                    // backround.show_height = (backround.show_height)? false : true;
                    // backround.update(tiles);
                    octaves -= step;
                    perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;

                case sf::Keyboard::Q:
                    height = (height)? false : true;
                    std::cout << height << std::endl;
                    break;

                case sf::Keyboard::W:
                    humidity = (humidity)? false : true;
                    std::cout << humidity << std::endl;
                    break;
                
                case sf::Keyboard::E:
                    temperature = !temperature;
                    std::cout << temperature << std::endl;
                    break;

                case sf::Keyboard::D:
                    // backround.show_tempature = (backround.show_tempature)? false : true;
                    // backround.update(tiles);
                    octaves += step;
                    perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;

                case sf::Keyboard::R:
                    seed = random(0, 9999999);
                    perlin.reseed(seed);
                    perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;
                
                case sf::Keyboard::P:
                    step += 0.01;
                    break;

                case sf::Keyboard::M:
                    step -= 0.01;
                    break;

                case sf::Keyboard::Z:
                    percistance -= step;
                    perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
                    break;

                case sf::Keyboard::C:
                    percistance += step;
                    perlin_height_sprite = generatePerlin(perlin, height_texture, octaves, percistance, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT);
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
        if (height = true)      {window.draw(perlin_height_sprite);}
        if (humidity = true)    {window.draw(perlin_humidity_sprite);}
        if (temperature = true) {window.draw(perlin_temperature_sprite);}


        // end the current frame
        window.display();
    }

    return 0;
}