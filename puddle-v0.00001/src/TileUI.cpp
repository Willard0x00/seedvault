#include "TileUI.h"

#include <GL/gl3w.h>
#include <SOIL/SOIL2.h>
#include "imgui.h"

#include "FileReader.h"

#include <iostream>

static const char TILE_FILE[] = "Data/Textures/tiles.txt";

TileUI::TileUI() :
	m_selected ( 0 )
{
	FileReader file(TILE_FILE);
	file.set_section("Tile");

	for (auto it = file.s_begin(); it != file.s_end(); ++it) {
		auto image = SOIL_load_OGL_texture(it->value.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		if (!image) {
			std::cout << "Error loading tile: " << it->value.c_str() << "\n";
		}
		m_tiles.push_back(image);
	}
}

TileUI::~TileUI() {
	glDeleteTextures(m_tiles.size(), &m_tiles[0]);
}

void TileUI::draw() {
	ImGui::Begin("Tiles");
	for (int i = 0; i < m_tiles.size(); ++i) {
		if (ImGui::ImageButton((void*)(intptr_t)m_tiles.at(i), {32, 32})) {
			m_selected = i;
		}
	}
	ImGui::End();
}