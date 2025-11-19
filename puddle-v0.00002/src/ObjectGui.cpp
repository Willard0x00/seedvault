#include "ObjectGui.h"

#include <imgui.h>

#include "ObjectComponent.h"
#include "SpriteComponent.h"
#include "Sprite.h"

ObjectGui::ObjectGui(Selection& selection, const CompactArray<Entity>& entities) :
	m_selection ( selection )
{
	for (int i = 0; i < entities.size(); ++i) {
		auto entity = entities.at(i);
		auto object = entity->get<ObjectComponent>();
		if (object) {
			auto sprite = entity->get<SpriteComponent>();
			if (sprite) {
				m_sprites.emplace_back(sprite);
			}
		}
	}
}

ObjectGui::~ObjectGui() {
	
}

void ObjectGui::setCursor(double x, double y) {
	m_transform.m_position = glm::vec3(x, y, 0);
}

ObjectCursor ObjectGui::getCursor() const {
	if (m_selection.m_index < m_sprites.size()) {
		return { m_transform, m_sprites[m_selection.m_index] };
	}
	return { m_transform, nullptr };
}

void ObjectGui::draw() {
	ImGui::Begin("Objects");

	for (unsigned int i = 0; i < m_sprites.size(); ++i) {
		auto sprite = m_sprites[i]->m_sprite;

		auto uvX = sprite->getSpriteUvWidth();
		auto uvY = sprite->getSpriteUvHeight();
		auto offsetX = sprite->getSpriteUvXOffset();
		auto offsetY = sprite->getSpriteUvYOffset();

		if (ImGui::ImageButton((void*)(intptr_t)sprite->getTexture(), { 48, 48 }, { 0, 0 }, { float(uvX + offsetX), float(uvY + offsetY) })) {
			m_selection.m_type = SelectionType::Object;
			m_selection.m_id = m_sprites[i]->m_entity->getId();
			m_selection.m_index = i;
		}
		if (i == 0 || i % 5 != 0) {
			ImGui::SameLine();
		}
	}
	ImGui::End();
}