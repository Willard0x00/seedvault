#include "Entity.h"

#include <imgui.h>
#include <imgui_stdlib.h>

#include <rapidjson/document.h>


Entity::Entity() :
	m_id ( -1 ),
	m_name ( "none" ),
	m_type ( "none" )
{}

Entity::~Entity() {

}

void Entity::load(void* document) {
	auto& doc = *static_cast<rapidjson::Value*>(document);

	m_id = doc["id"].GetInt();
	m_name = doc["name"].GetString();
	m_type = doc["type"].GetString();
}

int Entity::getId() const {
	return m_id;
}

void Entity::setId(int id) {
	m_id = id;
}

std::string Entity::getName() const {
	return m_name;
}

void Entity::setName(const std::string& name) {
	m_name = name;
}

std::string Entity::getType() const {
	return m_type;
}

void Entity::setType(const std::string& type) {
	m_type = type;
}

void Entity::drawGuiTree() {
	if (ImGui::CollapsingHeader((m_name + "##" + std::to_string((unsigned long long)this)).c_str())) {
		ImGui::Text("ID: ");
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_id).c_str());

		ImGui::InputText("Name", &m_name);
		ImGui::InputText("Type", &m_type);

		for (auto& component : m_components) {
			if (component) {
				component->drawGuiTree();
			}
		}
	}
}