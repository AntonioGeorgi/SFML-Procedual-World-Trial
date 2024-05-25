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
            // if (noise < 0.35) {
            //     noise = 0.0;
            // }
            // else if (noise >= 0.35 && noise < 0.5) {
            //     noise = 0.2;
            // }
            // else if (noise >= 0.5 && noise < 0.55) {
            //     noise = 0.4;
            // }
            // else if (noise >= 0.55 && noise < 0.65) {
            //     noise = 0.6;
            // }
            // else if (noise >= 0.65 && noise < 0.70) {
            //     noise = 0.8;
            // }
            // else {
            //     noise = 1;
            // }
            if (color == sf::Color::Green) {
                tiles[x + y * height ].height = noise;
            } else if (color == sf::Color::Blue) {
                tiles[x + y * height ].humidity = noise;
            }
            else if (color == sf::Color::Red) {
                tiles[x + y * height ].tempature = noise;
            }
            

            a = (noise) * 255;
            sf::Color image_color = color;
            image_color.a = a;
            image.setPixel(x, y, image_color);
        }
        std::cout << std::endl;
    }

    texture.loadFromImage(image);
}

void setWind(std::vector<Tile>& tiles, unsigned int width, unsigned int height) {
    float temp_diff;
    for (unsigned int y = 1; y < height - 1; y++) {
        for (unsigned int x = 1; x < width - 1; x++) {
            // horizontal
            temp_diff = tiles[(x - 1) + y * width].tempature -tiles[(x + 1) + y * width].tempature;
            tiles[x + y * width].sky_wind.x = temp_diff;
            // vertical
            temp_diff = tiles[x + (y - 1) * width].tempature -tiles[x + (y + 1) * width].tempature;
            tiles[x + y * width].sky_wind.y = temp_diff;
            // top-left -> down-right
            temp_diff = tiles[(x - 1) + (y - 1) * width].tempature -tiles[(x + 1) + (y + 1) * width].tempature;
            tiles[x + y * width].sky_wind.x += temp_diff/2;
            tiles[x + y * width].sky_wind.y += temp_diff/2;
            // bottom-left -> top-right
            temp_diff = tiles[(x - 1) + (y + 1) * width].tempature -tiles[(x + 1) + (y - 1) * width].tempature;
            tiles[x + y * width].sky_wind.x += temp_diff/2;
            tiles[x + y * width].sky_wind.y -= temp_diff/2;
        }
    }
}

void printWind(std::vector<Tile> tiles, unsigned int width, unsigned int height) {
    std::ofstream outFile("Wind_Map.txt");
    if (outFile.is_open()) {
        // Write data to the file
        for (unsigned int y = 1; y < height - 1; y++) {
            for (unsigned int x = 1; x < width - 1; x++) {
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
}

int random(int start, int fin) {
    return rand() % fin + start;
}