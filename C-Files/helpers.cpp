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
    for (unsigned int y = 0; y < height; y++) {
        unsigned int top_y   = (y == 0)? height - 1: y - 1;
        unsigned int down_y  = (y == height - 1)? 0 : y + 1;
        // std::cout << "top_y: " << top_y << ", down_y: " << down_y << std::endl;
        for (unsigned int x = 0; x < width; x++) {
            unsigned int left_x  = (x == 0)? width - 1: x - 1;
            unsigned int right_x = (x == width - 1)? 0 : x + 1;  
            // temperatures of the of 9 tile grid around focused tile
            float temp_left_top   = tiles[left_x + top_y * width].tempature;
            float temp_left_mid   = tiles[left_x + y * width].tempature;
            float temp_left_down  = tiles[left_x + down_y * width].tempature;
            float temp_mid_top    = tiles[x + top_y * width].tempature;
            float temp_mid_mid    = tiles[x + y * width].tempature;
            float temp_mid_down   = tiles[x + down_y * width].tempature;
            float temp_right_top  = tiles[right_x + top_y * width].tempature;
            float temp_right_mid  = tiles[right_x + y * width].tempature;
            float temp_right_down = tiles[right_x + down_y * width].tempature;

            // avarage temperature for 9 tile grid around focused tile
            float avarage_temp =   temp_left_top  + temp_mid_top  + temp_right_top 
                                 + temp_left_mid  + temp_mid_mid  + temp_right_mid 
                                 + temp_left_down + temp_mid_down + temp_right_down;
            avarage_temp /= 9;
            // the wind vetors l für left, m für mid, r für right, t für top, d für down; xy; von_zu
            float wind_lm_rm = 0, wind_mt_md = 0, wind_ld_rt = 0, wind_lt_rd = 0;
            // calulate winds but only from the focuesed tile to smaller neighbours, leads from focused tile outwards
            // -x --> +x
            float wind_lm = temp_mid_mid - temp_left_mid;
            float wind_rm = temp_mid_mid - temp_right_mid;
            wind_lm_rm -= (wind_lm > 0)? wind_lm : 0;
            wind_lm_rm += (wind_rm > 0)? wind_rm : 0;
            // -y --> +x
            float wind_md = temp_mid_mid - temp_mid_down;
            float wind_mt = temp_mid_mid - temp_mid_top;
            wind_mt_md -= (wind_mt > 0)? wind_mt : 0;
            wind_mt_md += (wind_md > 0)? wind_md : 0;
            // -x-y --> +x+y
            float wind_ld = temp_mid_mid - temp_left_down;
            float wind_rt = temp_mid_mid - temp_right_top;
            wind_ld_rt -= (wind_ld > 0)? wind_ld : 0;
            wind_ld_rt += (wind_rt > 0)? wind_rt : 0;
            // -x+y --> +x-y
            float wind_lt = temp_mid_mid - temp_left_top;
            float wind_rd = temp_mid_mid - temp_right_down;
            wind_lt_rd -= (wind_lt > 0)? wind_lt : 0;
            wind_lt_rd += (wind_rd > 0)? wind_rd : 0;

            // add wind_ld_rt to lm_rm und md_mt
            wind_lm_rm += wind_ld_rt / sqrt(2);
            wind_mt_md -= wind_ld_rt / sqrt(2);
            // add wind_lt_rd to lm_rm und md_mt
            wind_lm_rm += wind_lt_rd / sqrt(2);
            wind_mt_md += wind_lt_rd / sqrt(2);

            // safe wind to focused tile
            tiles[x + y * width].sky_wind.x = wind_lm_rm / avarage_temp;
            tiles[x + y * width].sky_wind.y = wind_mt_md / avarage_temp;
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

            Tile focused_tile  = tiles[x + y * width];
            float wind_x        = focused_tile.sky_wind.x;
            float wind_y        = focused_tile.sky_wind.y;
            bool wind_x_positiv = wind_x > 0;
            bool wind_y_positiv = wind_y > 0;

            if (wind_x_positiv) {
                
            } else {

            }
        }
    }
    //std::cout << "Execute" << std::endl;
}

void printWind(std::vector<Tile> tiles, unsigned int visibility_limit, unsigned int width, unsigned int height) {
    std::ofstream outFile("Wind_Map.txt");
    if (outFile.is_open()) {
        // Write data to the file
        for (unsigned int y = 0; y < height; y++) {
            for (unsigned int x = 0; x < width; x++) {
                float wind_x        = tiles[x + y * width].sky_wind.x;
                float wind_y        = tiles[x + y * width].sky_wind.y;
                bool wind_x_positiv = wind_x > 0;
                bool wind_y_positiv = wind_y > 0;
                bool ignore_x       = std::floor(wind_y / visibility_limit * wind_x); // 
                bool ignore_y       = std::floor(wind_x / visibility_limit * wind_y); // >1 --> wind_x deutlich größer wind_y

                // right row
                if (!ignore_x && !ignore_y) {
                    if (wind_x_positiv) {
                        if (!wind_y_positiv) {
                            const char arrow[] = "↗";
                            outFile << arrow;
                        } else {
                            const char arrow[] = "↘";
                            outFile << arrow;
                        }
                    } else if (!wind_x_positiv) {
                        if (!wind_y_positiv) {
                            const char arrow[] = "↖";
                            outFile << arrow;
                        } else {
                            const char arrow[] = "↙";
                            outFile << arrow;
                        }
                    }
                // left row
                } else if (ignore_y) {
                    if (wind_x_positiv) {
                        const char arrow[] = "→";
                        outFile << arrow;
                    } else {
                        const char arrow[] = "←";
                        outFile << arrow;
                    }
                // vertical row
                } else if (ignore_x) {
                    if (!wind_y_positiv) {
                        const char arrow[] = "↑";
                        outFile << arrow;
                    } else {
                        const char arrow[] = "↓";
                        outFile << arrow;
                    }
                } else {
                       const char arrow[] = "+";
                            outFile << arrow; 
                }            
            }
            // add end of line
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