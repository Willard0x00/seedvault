#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define __STDC_LIB_EXT1__
#include "stb_image_write.h"
#include "cxxopts.hpp"
#include <filesystem>
#include <string>
#include <iostream>

int main(int argc, const char* const* argv) {
	cxxopts::Options options("TileSheetSeperator", "seperates tile sheets into indiviual tiles and writes a png for each");
	options.add_options()
		("i, input", "File that holds the tile sheet", cxxopts::value<std::string>()->default_value(""))
		("o, output", "Output directory for the seperated tiles", cxxopts::value<std::string>()->default_value(""));

	auto result = options.parse(argc, argv);
	std::string input = result["input"].as<std::string>();
	std::string output = result["output"].as<std::string>();

	if (input.empty() || output.empty()) {
		std::cout << "Must provide an input and output directory" << "\n";
		return 1;
	}

	std::filesystem::path file(input);
	if (!std::filesystem::exists(file)) {
		std::cout << "No input file found [" << input << "]" << "\n";
		return 2;
	}

	int w = 0;
	int h = 0;
	int comp = 0;
	unsigned char* image = stbi_load(input.c_str(), &w, &h, &comp, 0);
	if (!image) {
		std::cout << "Failed to load image with stb, is it a valid png?" << "\n";
		return 3;
	}

	std::cout << "TileSheet loaded from [" << input << "]" << "\n";

	std::vector<std::vector<int>> tiles;
	int tilesX = 10;
	int tilesY = (h - 4) / 52;
	tiles.resize(tilesX * tilesY);

	for (auto& tile : tiles) {
		tile.resize(48 * 48);
	}

	auto skipXScanLine = [](int& pixel, int width) {
		pixel += width * 4;
		};

	auto skipYScanLine = [](int& pixel) {
		pixel += 4;
		};

	int size = w * h;
	int pixel = 0;
	int tilePixel = 0;
	int pixelRow = 0;
	int xFrames = 10;
	int tileRow = 0;

	auto imagePtr = reinterpret_cast<int*>(image);

	skipXScanLine(pixel, w);
	while (pixel < size) {
		int tile = tileRow * xFrames;
		int startingTilePixel = tilePixel;
		skipYScanLine(pixel);

		while (pixel % w != 0) {
			memcpy(&tiles[tile][tilePixel], imagePtr + pixel, sizeof(int));

			++pixel;
			++tilePixel;

			if (tilePixel % 48 == 0) {
				++tile;
				skipYScanLine(pixel);
				tilePixel = startingTilePixel;
			}
		}

		++pixelRow;
		tilePixel += 48;

		if (tilePixel == 48 * 48) {
			skipXScanLine(pixel, w);
			++tileRow;
			tilePixel = 0;
		}
	}

	stbi_image_free(image);

	std::filesystem::path outputDir(output);
	if (!std::filesystem::exists(outputDir) || !std::filesystem::is_directory(outputDir)) {
		std::filesystem::create_directory(outputDir);
	}

	std::cout << "Outputing to [" << output << "/]" << "\n";

	for (int i = 0; i < tiles.size(); ++i) {
		std::string outputName(output + "/" + std::to_string(i) + ".png");
		std::cout << "Wrote tile [" << i + 1 << "/" << tiles.size() << "]" << "\r";

		int result = stbi_write_png(outputName.c_str(), 48, 48, 4, &tiles[i][0], 0);
	}

	std::cout << "\n";

	return 0;
}