
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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

            switch (event.key.scancode)
                {
                case sf::Keyboard::A:
                    break;

                case sf::Keyboard::W:
                    break;

                case sf::Keyboard::D:
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
        window.draw(shape);

        // end the current frame
        window.display();
    }

    return 0;
}