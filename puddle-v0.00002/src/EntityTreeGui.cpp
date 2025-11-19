#include "EntityTreeGui.h"

#include <imgui.h>

#include "Entity.h"

EntityTreeGui::EntityTreeGui(Selection& selection, removeEntityFn removeEntityFn, duplicateEntityFn duplicateEntityFn) :
	m_selection(selection),
	m_removeEntityFn(removeEntityFn),
	m_duplicateEntityFn(duplicateEntityFn)
{}

EntityTreeGui::~EntityTreeGui()
{}

void EntityTreeGui::draw() {
	ImGui::Begin("Entity Tree");

	if (m_selection.m_entities.size() == 0) {
		ImGui::Text("There are no selected entities");
	}

	std::vector<Entity*> addAfter;
	auto it = m_selection.m_entities.begin();
	while (it != m_selection.m_entities.end()) {

		ImGui::Text("                                ");
		ImGui::SameLine();
		if (ImGui::Button(("Duplicate##" + std::to_string((unsigned long long)(*it))).c_str())) {
			auto dup = m_duplicateEntityFn(*it);
			addAfter.push_back(dup);
		}
		ImGui::SameLine();
		if (ImGui::Button(("Delete##" + std::to_string((unsigned long long)(*it))).c_str())) {
			m_removeEntityFn(*it);
			it = m_selection.m_entities.erase(it);
		}
		else {
			(*it)->drawGuiTree();
			++it;
		}
	}

	if (addAfter.size() > 0) {
		for (auto dup : addAfter) {
			m_selection.m_entities.push_back(dup);
		}
	}

	ImGui::End();
}