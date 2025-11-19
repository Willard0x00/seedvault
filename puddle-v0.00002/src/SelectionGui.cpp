#include "SelectionGui.h"

#include <imgui.h>

SelectionGui::SelectionGui(Selection& selection, bool p_center, bool p_corner) :
	m_selection ( selection ),
	m_center ( p_center ),
	m_corner ( p_corner )
{

}

SelectionGui::~SelectionGui() {

}

void SelectionGui::draw() {
	ImGui::Begin("Selection");


	if (ImGui::Button("Clear")) {
		m_selection.clear();
		m_selection.clearGrab();
	}

	ImGui::SameLine();
	ImGui::Checkbox("Center", &m_center);
	if (m_center && m_corner) m_corner = false;
	ImGui::SameLine();
	ImGui::Checkbox("Corner", &m_corner);
	if (m_center && m_corner) m_center = false;

	ImGui::End();
}