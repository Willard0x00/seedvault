#include "MenuUI.h"

#include <imgui.h>

MenuUI::MenuUI(std::function<void(std::string)> saveMapFn) :
	m_saveMapFn ( saveMapFn )
{}

MenuUI::~MenuUI()
{}

void MenuUI::draw() {
	ImGui::Begin("Menu");

	if (ImGui::Button("save map")) {
		m_saveMapFn("Data/Maps/default.kart");
	}

	ImGui::End();
}