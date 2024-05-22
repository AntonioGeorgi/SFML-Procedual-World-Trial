
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/helpers.h"

const int TILE_SIZE   = 1;
const int GRID_WIDTH  = 1000;
const int GRID_HEIGHT = 1000;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT), "SFML Prodcedual World Trial!");

    sf::CircleShape shape(TILE_SIZE / 2);
    shape.setFillColor(sf::Color::Magenta);

    Backround backround(GRID_HEIGHT, TILE_SIZE);
    std::vector<Tile> tiles(GRID_WIDTH * GRID_HEIGHT);

    for (size_t i = 0; i < tiles.size(); i++)
    {
        tiles[i].height     = i / GRID_WIDTH * 255 / GRID_HEIGHT;
        tiles[i].humidity   = i * 10;
        tiles[i].tempature  = i % GRID_HEIGHT * 255 / GRID_WIDTH;
    }
    backround.update(tiles);

    // run the program as long as the window is open
    while (window.isOpen())
    {        // check all the window's events that were triggered since the last iteration of the loop
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
                    backround.show_height = (backround.show_height)? false : true;
                    backround.update(tiles);
                    break;

                case sf::Keyboard::W:
                    backround.show_humidity = (backround.show_humidity)? false : true;
                    backround.update(tiles);
                    break;

                case sf::Keyboard::D:
                    backround.show_tempature = (backround.show_tempature)? false : true;
                    backround.update(tiles);
                    break;

                case sf::Keyboard::S:
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
        window.draw(backround);
        // window.draw(shape);

        // end the current frame
        window.display();
    }

    return 0;
}