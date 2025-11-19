#include <iostream>
#include <string>
#include <cmath>

#include "cxxopts.hpp"
#include "bmp.hpp"

int main(int argc, char* argv[]) {
    cxxopts::Options options("spritesheet", "Creates empty sprite sheed with the correct dimensions and padding");

    options.add_options()
    ("s,sprites", "num of sprites", cxxopts::value<int>())
    ("p,padding", "sprite padding", cxxopts::value<int>())
    ("w,spriteWidth", "width of the sprite", cxxopts::value<int>())
    ("h,spriteHeight", "height of the sprite", cxxopts::value<int>())
    ("f,file", "file name", cxxopts::value<std::string>())
    ;

    auto result = options.parse(argc, argv);

    BMP bmp;


    int sprites = result["sprites"].as<int>();
    int padding = result["padding"].as<int>();
    int spriteWidth = result["spriteWidth"].as<int>();
    int spriteHeight = result["spriteHeight"].as<int>();
    std::string fileName = result["file"].as<std::string>();
    fileName.append(".bmp");

    struct pixel {
        char a = 0, b = 255, g = 0, r = 0;
    } pixel;

    int spritesPerRow = sprites % 10;
    int columns = ceil(sprites / 10.0);
    if (sprites >= 10) {
        spritesPerRow = 10;
    }

    int width = spriteWidth * spritesPerRow;
    int height = spriteHeight * columns;

    std::cout << "sprites per row: " << spritesPerRow << "\n";
    std::cout << "columns: " << columns << "\n";

    bmp.m_width = width + spritesPerRow * padding + padding;
    bmp.m_height = height + columns * padding + padding;
    bmp.m_imageSize = bmp.m_width * bmp.m_height * 4;
    bmp.m_fileSize = 122 + bmp.m_imageSize;

    std::cout << "width: " << bmp.m_width << " height: " << bmp.m_height << "\n";

    for (int y = 0; y < bmp.m_height; ++y) {
        for (int x = 0; x < bmp.m_width; ++x) {
            
            for (int i = 0; i < padding; ++i) {
                if ((x - i) % (spriteWidth + padding) == 0) {
                    pixel = {0, 0, 0, 0};
                }

                if ((y - i) % (spriteHeight + padding) == 0) {
                    pixel = {0, 0, 0, 0};
                }
            }

            bmp.m_pixelData.push_back(pixel.r);
            bmp.m_pixelData.push_back(pixel.g);
            bmp.m_pixelData.push_back(pixel.b);
            bmp.m_pixelData.push_back(pixel.a);
            pixel.a = 255;
            pixel.b = 255;
            pixel.g = 255;
            pixel.r = 255;
        }
    }

    FILE* f;
    f = fopen(fileName.c_str(), "wb");

    fwrite((void*)&bmp.m_signature, sizeof(bmp.m_signature), 1, f);
    fwrite((void*)&bmp.m_fileSize, sizeof(bmp.m_fileSize), 1, f);
    fwrite((void*)&bmp.m_reserved, sizeof(bmp.m_reserved), 1, f);
    fwrite((void*)&bmp.m_dataOffset, sizeof(bmp.m_dataOffset), 1, f);
    fwrite((void*)&bmp.m_size, sizeof(bmp.m_size), 1, f);
    fwrite((void*)&bmp.m_width, sizeof(bmp.m_width), 1, f);
    fwrite((void*)&bmp.m_height, sizeof(bmp.m_height), 1, f);
    fwrite((void*)&bmp.m_planes, sizeof(bmp.m_planes), 1, f);
    fwrite((void*)&bmp.m_bitsPerPixel, sizeof(bmp.m_bitsPerPixel), 1, f);
    fwrite((void*)&bmp.m_compression, sizeof(bmp.m_compression), 1, f);
    fwrite((void*)&bmp.m_imageSize, sizeof(bmp.m_imageSize), 1, f);
    fwrite((void*)&bmp.m_xPixelsPerM, sizeof(bmp.m_xPixelsPerM), 1, f);
    fwrite((void*)&bmp.m_yPixelsPerM, sizeof(bmp.m_yPixelsPerM), 1, f);
    fwrite((void*)&bmp.m_colorsUsed, sizeof(bmp.m_colorsUsed), 1, f);
    fwrite((void*)&bmp.m_importantColors, sizeof(bmp.m_importantColors), 1, f);
    fwrite((void*)&bmp.m_bitMasks.m_red, sizeof(bmp.m_bitMasks.m_red), 1, f);
    fwrite((void*)&bmp.m_bitMasks.m_green, sizeof(bmp.m_bitMasks.m_green), 1, f);
    fwrite((void*)&bmp.m_bitMasks.m_blue, sizeof(bmp.m_bitMasks.m_blue), 1, f);
    fwrite((void*)&bmp.m_bitMasks.m_alpha, sizeof(bmp.m_bitMasks.m_alpha), 1, f);
    fwrite((void*)&bmp.m_lcsWindowsColorSpace, sizeof(bmp.m_lcsWindowsColorSpace), 1, f);
    fwrite((void*)&bmp.m_ciexyzEndpoints, sizeof(bmp.m_ciexyzEndpoints), 1, f);
    fwrite((void*)&bmp.m_redGamma, sizeof(bmp.m_redGamma), 1, f);
    fwrite((void*)&bmp.m_greenGamma, sizeof(bmp.m_greenGamma), 1, f);
    fwrite((void*)&bmp.m_blueGamma, sizeof(bmp.m_blueGamma), 1, f);

    fwrite((void*)&bmp.m_pixelData[0], bmp.m_imageSize, 1, f);

    fclose(f);

    return 0;
}