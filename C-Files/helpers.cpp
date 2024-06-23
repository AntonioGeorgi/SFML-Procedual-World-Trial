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
                tiles[x + y * height ].temperature = noise;
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
                image_color.a = 255 * tiles[x + y * height ].temperature;
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
            std::vector<float> tile_temps;
            tile_temps.resize(9);
            tile_temps[0] = tiles[x + y * width].temperature;            // temp_mid_mid
            tile_temps[1] = tiles[left_x + top_y * width].temperature;   // temp_left_top
            tile_temps[2] = tiles[left_x + y * width].temperature;       // temp_left_mid
            tile_temps[3] = tiles[left_x + down_y * width].temperature;  // temp_left_down
            //printf("1.4");
            tile_temps[4] = tiles[x + top_y * width].temperature;        // temp_mid_top
            tile_temps[5] = tiles[x + down_y * width].temperature;       // temp_mid_down
            tile_temps[6] = tiles[right_x + top_y * width].temperature;  // temp_right_top
            tile_temps[7] = tiles[right_x + y * width].temperature;      // temp_right_mid
            tile_temps[8] = tiles[right_x + down_y * width].temperature; // temp_right_down
            //printf("1.8");
            std::vector<float> original_temps = tile_temps;
            // avarage temperature for 9 tile grid around focused tile
            float sum_temps = tile_temps[0];
            for (size_t i = 1; i < tile_temps.size(); i++)
            {
                if (tile_temps[i] < tile_temps[0]) {
                    sum_temps += tile_temps[i];
                } else 
                {
                    tile_temps.erase(tile_temps.begin() + i);
                    i--;
                }
            }
            bool high_temps = true;
            float avarage_temp;
            while (high_temps) 
            {
                high_temps = false;
                avarage_temp = sum_temps / tile_temps.size();
                for (size_t i = 1; i < tile_temps.size(); i++)
                {
                    if (avarage_temp < tile_temps[i]) {
                        sum_temps -= tile_temps[i];
                        high_temps = true;
                        tile_temps.erase(tile_temps.begin() + i);
                    }
                }
            }
            // now we have an avarage temp that allows us to equally distribute the temp from the center tile to it's lowest temp neighbours
            // all we need to do now is find out which neighbours are the lowest and then set the wind.
            for (size_t i = 1; i < tile_temps.size(); i++)
            {
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[left_x  + top_y  * width].temperature)? avarage_temp - tile_temps[i] : 0;
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[left_x  + y      * width].temperature)? avarage_temp - tile_temps[i] : 0;
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[left_x  + down_y * width].temperature)? avarage_temp - tile_temps[i] : 0;
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[x       + top_y  * width].temperature)? avarage_temp - tile_temps[i] : 0;
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[x       + down_y * width].temperature)? avarage_temp - tile_temps[i] : 0;
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[right_x + top_y  * width].temperature)? avarage_temp - tile_temps[i] : 0;
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[right_x + y      * width].temperature)? avarage_temp - tile_temps[i] : 0;
                tiles[x + y * width].sky_wind[i - 1] = (tile_temps[i] == tiles[right_x + down_y * width].temperature)? avarage_temp - tile_temps[i] : 0;
            }
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

            // temp_left_top
            tiles[left_x + top_y  * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[0];
            tiles[x + y           * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[0];   
            // temp_left_mid
            tiles[left_x + y      * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[1];
            tiles[x      + y      * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[1];       
            // temp_left_down
            tiles[left_x + down_y * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[2];
            tiles[x      + y      * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[2];
            // temp_mid_top
            tiles[x + top_y  * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[3];
            tiles[x + y      * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[3];      
            // temp_mid_down
            tiles[x + down_y * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[4];
            tiles[x + y      * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[4];       
            // temp_right_top
            tiles[right_x + top_y  * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[5];
            tiles[x       + y      * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[5]; 
            // temp_right_mid
            tiles[right_x + y      * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[6];
            tiles[x       + y      * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[6];    
            // temp_right_down            
            tiles[right_x + down_y * width].temperature += wind_impacts * tiles[x + y * width].sky_wind[7];
            tiles[x       + y      * width].temperature -= wind_impacts * tiles[x + y * width].sky_wind[7];
        }
    }
    //std::cout << "Execute" << std::endl;
}

// void printWind(std::vector<Tile> tiles, unsigned int visibility_limit, unsigned int width, unsigned int height) {
//     std::ofstream outFile("Wind_Map.txt");
//     if (outFile.is_open()) {
//         // Write data to the file
//         for (unsigned int y = 0; y < height; y++) {
//             for (unsigned int x = 0; x < width; x++) {
//                 float wind_x        = tiles[x + y * width].sky_wind.x;
//                 float wind_y        = tiles[x + y * width].sky_wind.y;
//                 bool wind_x_positiv = wind_x > 0;
//                 bool wind_y_positiv = wind_y > 0;
//                 bool ignore_x       = std::floor(wind_y / visibility_limit * wind_x); // 
//                 bool ignore_y       = std::floor(wind_x / visibility_limit * wind_y); // >1 --> wind_x deutlich größer wind_y

//                 // right row
//                 if (!ignore_x && !ignore_y) {
//                     if (wind_x_positiv) {
//                         if (!wind_y_positiv) {
//                             const char arrow[] = "↗";
//                             outFile << arrow;
//                         } else {
//                             const char arrow[] = "↘";
//                             outFile << arrow;
//                         }
//                     } else if (!wind_x_positiv) {
//                         if (!wind_y_positiv) {
//                             const char arrow[] = "↖";
//                             outFile << arrow;
//                         } else {
//                             const char arrow[] = "↙";
//                             outFile << arrow;
//                         }
//                     }
//                 // left row
//                 } else if (ignore_y) {
//                     if (wind_x_positiv) {
//                         const char arrow[] = "→";
//                         outFile << arrow;
//                     } else {
//                         const char arrow[] = "←";
//                         outFile << arrow;
//                     }
//                 // vertical row
//                 } else if (ignore_x) {
//                     if (!wind_y_positiv) {
//                         const char arrow[] = "↑";
//                         outFile << arrow;
//                     } else {
//                         const char arrow[] = "↓";
//                         outFile << arrow;
//                     }
//                 } else {
//                        const char arrow[] = "+";
//                             outFile << arrow; 
//                 }            
//             }
//             // add end of line
//             outFile << std::endl;
//         }
//         // Close the file
//         outFile.close();
//     } else {
//         std::cout << "Unable to open file for writing." << std::endl;
//     }
//     //std::cout << "Print" << std::endl;
// }

void printTemperature(std::vector<Tile> tiles, std::ofstream& outFile, unsigned int width, unsigned int height, bool sum_only) {
    if (outFile.is_open()) {
        double temp_sum = 0;
        // Write data to the file
        outFile.precision(5);
        if (!sum_only) 
        {
            printf("output Temperature \n");
            outFile << "output Temperature" << std::endl;
        }
        for (unsigned int y = 0; y < height; y++) {
            for (unsigned int x = 0; x < width; x++) {
                float temperature = tiles[x + y * width].temperature;
                temp_sum += temperature;
                if (!sum_only) 
                {
                    printf("%.5f, ", temperature);
                    outFile << temperature << ", ";
                }
            }
            if (!sum_only) 
            {
            std::cout << std::endl;
            outFile << std::endl;
            }
        }
        printf("Sum Temperature: %.5f \n" , temp_sum);
        outFile << "Sum Temperature: " << temp_sum << std::endl;
        // // Close the file
        // outFile.close();
    } else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}               

int random(int start, int fin) {
    return rand() % fin + start;
}