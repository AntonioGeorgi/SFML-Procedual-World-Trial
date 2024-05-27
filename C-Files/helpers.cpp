#include "..\Headers\helpers.h"

// sf::Sprite generatePerlin(siv::PerlinNoise& perlin, sf::Texture& texture, double octaves, double persistance, unsigned int width, unsigned int height) {
//     double x = 0;
//     double y = 0;
//     double noise;
//     double a;
//     sf::Color color;

//     sf::Image image;
//     image.create(width, height, sf::Color::Red);

//     double xLim = width;
//     double yLim = height;

//     for (x = 0; x < xLim; x++) {
//         for (y = 0; y < yLim; y++) {

//             noise = perlin.octave2D_01((x / width), (y / height), octaves, persistance);
//             if (noise < 0.35) {
//                 noise = 0.0;
//                 color = sf::Color::Blue;
//             }
//             else if (noise >= 0.35 && noise < 0.5) {
//                 noise = 0.2;
//                 color = sf::Color::Blue;
//             }
//             else if (noise >= 0.5 && noise < 0.55) {
//                 noise = 0.4;
//                 color = sf::Color::Yellow;
//             }
//             else if (noise >= 0.55 && noise < 0.65) {
//                 noise = 0.6;
//                 color = sf::Color::Green;
//             }
//             else if (noise >= 0.65 && noise < 0.70) {
//                 noise = 0.8;
//                 color = sf::Color::Green;
//             }
//             else if (noise >= 0.70 && noise < 0.75) {
//                 noise = 1;
//                 color = sf::Color(169, 169, 169);
//             }
//             else if (noise >= 0.75) {
//                 color = sf::Color::White;
//             }

//             a = (noise) * 255;
//             //color.a = a;
//             //color = sf::Color(255, 255, 255, a);
//             image.setPixel(x, y, color);
//         }
//     }

//     texture.loadFromImage(image);
//     sf::Sprite sprite(texture);
//     sprite.setPosition(0, 0);

//     return sprite;
// }

void generatePerlinTexture(siv::PerlinNoise& perlin, sf::Texture& texture, std::vector<Tile>& tiles, double octaves, double persistance, unsigned int width, unsigned int height, sf::Color color) {
    float noise;
    short a;

    sf::Image image;
    image.create(width, height, sf::Color::White);

    for (double y = 0; y < height; y++) {
        for (double x = 0; x < width; x++) {

            noise = perlin.octave2D_01((x / width), (y / height), octaves, persistance);

            if (color == sf::Color::Green) {
                tiles[x + y * height ].height = noise;
            } else if (color == sf::Color::Blue) {
                tiles[x + y * height ].humidity = noise;
            } else if (color == sf::Color::Red) {
                tiles[x + y * height ].tempature = noise;
            }
            a = (noise) * 255;
            sf::Color image_color = color;
            image_color.a = a;
            image.setPixel(x, y, image_color);
        }
    }

    texture.loadFromImage(image);
}

void updateTexture(sf::Texture& texture, std::vector<Tile> tiles, unsigned int width, unsigned int height, sf::Color color) {
    sf::Image image;
    image.create(width, height, sf::Color::White);

    for (double y = 0; y < height; y++) {
        for (double x = 0; x < width; x++) {
            sf::Color image_color = color;
            if (color == sf::Color::Green) {
                image_color.a = 255 * tiles[x + y * height ].height ;
            } else if (color == sf::Color::Blue) {
                image_color.a = 255 * tiles[x + y * height ].humidity;
            } else if (color == sf::Color::Red) {
                image_color.a = 255 * tiles[x + y * height ].tempature;
            }
            image.setPixel(x, y, image_color);
        }
    }
    texture.loadFromImage(image);
}

void setWind(std::vector<Tile>& tiles, unsigned int width, unsigned int height) {
    float temp_diff;
    for (unsigned int y = 0; y < height; y++) {
        unsigned int top_y   = (y == 0)? height - 1: y - 1;
        unsigned int down_y  = (y == height - 1)? 0 : y + 1;
        // std::cout << "top_y: " << top_y << ", down_y: " << down_y << std::endl;
        for (unsigned int x = 0; x < width; x++) {
            unsigned int left_x  = (x == 0)? width - 1: x - 1;
            unsigned int right_x = (x == width - 1)? 0 : x + 1;   
            // std::cout << "left_x: " << left_x << ", right_x: " << right_x << std::endl;         
            // std::cout << "neighbours Set" << std::endl;         
            // horizontal
            temp_diff = tiles[left_x + y * width].tempature -tiles[right_x + y * width].tempature;
            tiles[x + y * width].sky_wind.x = temp_diff;
            // std::cout << "horizontal" << std::endl;
            // vertical
            temp_diff = tiles[x + top_y * width].tempature -tiles[x + down_y * width].tempature;
            tiles[x + y * width].sky_wind.y = temp_diff;
            // std::cout << "vertical" << std::endl; 
            // top-left -> down-right
            temp_diff = tiles[left_x + top_y * width].tempature -tiles[right_x + down_y * width].tempature;
            tiles[x + y * width].sky_wind.x += temp_diff/2;
            tiles[x + y * width].sky_wind.y += temp_diff/2;
            // std::cout << "top-left -> down-right" << std::endl; 
            // bottom-left -> top-right
            temp_diff = tiles[left_x + down_y * width].tempature -tiles[right_x + top_y * width].tempature;
            tiles[x + y * width].sky_wind.x += temp_diff/2;
            tiles[x + y * width].sky_wind.y -= temp_diff/2;
            // std::cout << "bottom-left -> top-right" << std::endl; 
        }
    }   
    // std::cout << "Set" << std::endl;
}

void executeWind(std::vector<Tile>& tiles, float wind_impacts, unsigned int width, unsigned int height) {
    for (unsigned int y = 0; y < height; y++) {
        unsigned int top_y   = (y == 0)? height - 1: y - 1;
        unsigned int down_y  = (y == height - 1)? 0 : y + 1;
        for (unsigned int x = 0; x < width; x++) {
            unsigned int left_x  = (x == 0)? width - 1: x - 1;
            unsigned int right_x = (x == width - 1)? 0 : x + 1; 
            float sky_wind_x = tiles[x + y * width].sky_wind.x;
            float sky_wind_y = tiles[x + y * width].sky_wind.y;
            // horizontal
            tiles[left_x + y * width].tempature -= wind_impacts * sky_wind_x;
            tiles[right_x + y * width].tempature += wind_impacts * sky_wind_x;
            // vertical
            tiles[x + top_y * width].tempature -= wind_impacts * sky_wind_y;
            tiles[x + down_y * width].tempature += wind_impacts * sky_wind_y;

            if (((sky_wind_x > 0) && sky_wind_y > 0) || ((sky_wind_x < 0) && sky_wind_y < 0))
            {
                // top-left -> down-right
                tiles[left_x + top_y * width].tempature -= wind_impacts * sqrt(pow(sky_wind_x, 2) + pow(sky_wind_y, 2));
                tiles[right_x + down_y * width].tempature += wind_impacts * sqrt(pow(sky_wind_x, 2) + pow(sky_wind_y, 2));
            } else if ((sky_wind_x == 0) || (sky_wind_y == 0)) {
                // bottom-left -> top-right
                tiles[left_x + down_y * width].tempature -= wind_impacts * sqrt(pow(sky_wind_x, 2) + pow(sky_wind_y, 2));
                tiles[right_x + top_y * width].tempature += wind_impacts * sqrt(pow(sky_wind_x, 2) + pow(sky_wind_y, 2));
            } else {
                // bottom-left -> top-right
                tiles[left_x + down_y * width].tempature -= wind_impacts * sqrt(pow(sky_wind_x, 2) + pow(sky_wind_y, 2));
                tiles[right_x + top_y * width].tempature += wind_impacts * sqrt(pow(sky_wind_x, 2) + pow(sky_wind_y, 2));
            }
        }
    }
    //std::cout << "Execute" << std::endl;
}

void printWind(std::vector<Tile> tiles, unsigned int width, unsigned int height) {
    std::ofstream outFile("Wind_Map.txt");
    if (outFile.is_open()) {
        // Write data to the file
        for (unsigned int y = 0; y < height; y++) {
            for (unsigned int x = 0; x < width; x++) {
                // right row
                if (tiles[x + y * width].sky_wind.x > 0) {
                    if (tiles[x + y * width].sky_wind.y < 0) {
                        const char arrow[] = "↗";
                        outFile << arrow;
                    } else if (tiles[x + y * width].sky_wind.y == 0) {
                        const char arrow[] = "→";
                        outFile << arrow;
                    } else  if (tiles[x + y * width].sky_wind.y > 0) {
                        const char arrow[] = "↘";
                        outFile << arrow;
                    }
                // left row
                } else if (tiles[x + y * width].sky_wind.x < 0) {
                    if (tiles[x + y * width].sky_wind.y < 0) {
                        const char arrow[] = "↖";
                        outFile << arrow;
                    } else if (tiles[x + y * width].sky_wind.y == 0) {
                        const char arrow[] = "←";
                        outFile << arrow;
                    } else if (tiles[x + y * width].sky_wind.y > 0) {
                        const char arrow[] = "↙";
                        outFile << arrow;
                    }
                // vertical row
                } else if (tiles[x + y * width].sky_wind.x == 0) {
                    if (tiles[x + y * width].sky_wind.y < 0) {
                        const char arrow[] = "↑";
                        outFile << arrow;
                    } else if (tiles[x + y * width].sky_wind.y > 0) {
                        const char arrow[] = "↓";
                        outFile << arrow;
                    }
                }            
            }
            outFile << std::endl;
        }
        // Close the file
        outFile.close();
    } else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
    //std::cout << "Print" << std::endl;
}

int random(int start, int fin) {
    return rand() % fin + start;
}