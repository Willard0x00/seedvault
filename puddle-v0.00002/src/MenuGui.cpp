#include "MenuGui.h"

#include <imgui.h>
#include <imgui_stdlib.h>

#include "FileDialog.h"

#include "DetachedProcess.h"

constexpr const char* g_popupNewMap = "New Map";
constexpr const char* g_popupLoadMap = "Load Map";
constexpr const char* g_popupSpriteSheet = "Sprite Sheet";
constexpr const char* g_defaultMapDirectory = "Data/Maps/";

MenuGui::MenuGui(NewMapFn newMapFn, SaveMapFn saveMapFn, LoadMapFn loadMapFn, SaveEntitiesFn saveEntitiesFn, LoadEntitiesFn loadEntitiesFn, const std::string* mapName) :
	m_newMapFn ( newMapFn ),
	m_saveMapFn ( saveMapFn ),
	m_loadMapFn ( loadMapFn ),
	m_saveEntitiesFn ( saveEntitiesFn ),
	m_loadEntitiesFn ( loadEntitiesFn ),
	m_mapName ( mapName ),
	m_openNewMapPopup ( false ),
	m_openLoadMapPopup ( false ),
	m_openSpriteSheetPopup ( false )
{}

MenuGui::~MenuGui()
{}

void MenuGui::draw() {
	if (ImGui::BeginMainMenuBar()) {
		
		drawFile();

		drawEdit();

		if (ImGui::Button("Run")) {
			m_saveMapFn("tmp");
			m_saveEntitiesFn("tmp");
			DetachedProcess game("2.18 -m game -k tmp");
		}

		ImGui::EndMainMenuBar();
	}

	popUp();
}

void MenuGui::drawFile() {
	if (ImGui::BeginMenu("File")) {

		if (ImGui::MenuItem("New Map")) {
			m_openNewMapPopup = true;
		}

		if (ImGui::MenuItem("Save Map")) {
			std::string file = save_single_file(m_mapName->c_str()).c_str();
			file = file.substr(0, file.find_last_of("."));
			m_saveMapFn(file.c_str());
			m_saveEntitiesFn(file.c_str());
		}

		if (ImGui::MenuItem("Load Map")) {
			m_openLoadMapPopup = true;
		}

		ImGui::EndMenu();
	}
}

void MenuGui::drawEdit() {
	if (ImGui::BeginMenu("Edit")) {
		
		if (ImGui::MenuItem("New Sprite Sheet")) {
			m_openSpriteSheetPopup = true;
		}



		ImGui::EndMenu();
	}
}

void MenuGui::popUp() {
	if (m_openNewMapPopup) {
		ImGui::OpenPopup(g_popupNewMap);
		m_openNewMapPopup = false;
	}

	if (m_openLoadMapPopup) {
		ImGui::OpenPopup(g_popupLoadMap);
		m_openLoadMapPopup = false;
	}

	if (m_openSpriteSheetPopup) {
		ImGui::OpenPopup(g_popupSpriteSheet);
		m_openSpriteSheetPopup = false;
	}

	if (ImGui::BeginPopupModal(g_popupNewMap)) {
		ImGui::PushItemWidth(100);
		ImGui::InputInt("Width", &m_createNewMapDialog.width);
		ImGui::SameLine();
		ImGui::InputInt("Height", &m_createNewMapDialog.height);
		ImGui::InputInt("Base Tile", &m_createNewMapDialog.tile);
		ImGui::PushItemWidth(200);
		ImGui::InputText("Name", &m_createNewMapDialog.name);
		ImGui::PopItemWidth();

		if (m_createNewMapDialog.tile < 0) {
			m_createNewMapDialog.tile = 0;
		}
		else if (m_createNewMapDialog.tile > std::numeric_limits<uint16_t>::max()) {
			m_createNewMapDialog.tile = std::numeric_limits<uint16_t>::max();
		}

		if (ImGui::Button("Create")) {
			m_newMapFn(m_createNewMapDialog);
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::PopItemWidth();
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal(g_popupLoadMap)) {
		ImGui::Text("Warning: Save your current progress before loading a new map");

		if (ImGui::Button("Continue")) {
			std::string file = open_single_file().c_str();
			file = file.substr(0, file.find_last_of("."));

			m_loadMapFn((file + ".kart").c_str());
			m_loadEntitiesFn((file + ".json").c_str());
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal(g_popupSpriteSheet)) {
		ImGui::PushItemWidth(200);
		ImGui::Text("Pixel Padding Between Sprites: 2");
		ImGui::InputInt("Number of Sprites", &m_spriteSheetDialog.m_sprites);
		ImGui::InputInt("Sprite Width", &m_spriteSheetDialog.m_width);
		ImGui::InputInt("Sprite Height", &m_spriteSheetDialog.m_height);
		ImGui::PushItemWidth(300);
		ImGui::InputText("File Name", &m_spriteSheetDialog.m_file);

		if (ImGui::Button("Create")) {
			std::string cmd;
			cmd.append("Tools/SpriteSheetTool.exe ");
			cmd.append("-s ");
			cmd.append(std::to_string(m_spriteSheetDialog.m_sprites) + " ");
			cmd.append("-p ");
			cmd.append(std::to_string(m_spriteSheetDialog.m_padding) + " ");
			cmd.append("-w ");
			cmd.append(std::to_string(m_spriteSheetDialog.m_width) + " ");
			cmd.append("-h ");
			cmd.append(std::to_string(m_spriteSheetDialog.m_height) + " ");
			cmd.append("-f ");
			cmd.append(m_spriteSheetDialog.m_file);
			DetachedProcess spriteSheetTool(cmd);
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			ImGui::CloseCurrentPopup();
		}
		
		ImGui::EndPopup();
	}
}