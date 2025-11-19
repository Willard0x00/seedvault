#include "TileGui.h"

#include <filesystem>

#include <GL/gl3w.h>
#include <SOIL/SOIL2.h>
#include <imgui.h>

#include "Log.h"

static const char* g_tileFolder = "Data/Maps/Tiles";

TileGui::TileGui(Selection& selection) :
	m_selection ( selection )
{
	const std::filesystem::path directory(g_tileFolder);

	for (const auto& dirEntry : std::filesystem::directory_iterator{ directory }) {
		if (dirEntry.is_regular_file()) {
			auto image = SOIL_load_OGL_texture(dirEntry.path().string().c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
			if (!image) {
				Log::get().write(L_ERROR, "Failed to load tile for TileGui: ", dirEntry.path().string().c_str());
			}
			m_tiles.push_back(image);
		}
	}
}

TileGui::~TileGui() {
	if (m_tiles.size() > 0) {
		glDeleteTextures(m_tiles.size(), &m_tiles[0]);
	}
}

void TileGui::draw() {
	ImGui::Begin("Tiles");
	for (unsigned int i = 0; i < m_tiles.size(); ++i) {
		if (ImGui::ImageButton((void*)(intptr_t)m_tiles.at(i), { 48, 48 })) {
			m_selection.m_type = SelectionType::TILE;
			m_selection.m_id = i;
		}
		if (i == 0 || i % 5 != 0) {
			ImGui::SameLine();
		}
	}
	ImGui::End();
}