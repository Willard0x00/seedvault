#include "EnemyGui.h"

#include <imgui.h>

#include "EnemyComponent.h"
#include "SpriteComponent.h"
#include "Sprite.h"

EnemyGui::EnemyGui(Selection& selection, const CompactArray<Entity>& entities) :
	m_selection(selection)
{
	for (int i = 0; i < entities.size(); ++i) {
		auto entity = entities.at(i);
		auto enemy = entity->get<EnemyComponent>();
		if (enemy) {
			auto sprite = entity->get<SpriteComponent>();
			if (sprite) {
				m_sprites.emplace_back(sprite);
			}
		}
	}
}

EnemyGui::~EnemyGui() {

}

void EnemyGui::setCursor(double x, double y) {
	m_transform.m_position = glm::vec3(x, y, 0);
}

EnemyCursor EnemyGui::getCursor() const {
	if (m_selection.m_index < m_sprites.size()) {
		return { m_transform, m_sprites[m_selection.m_index] };
	}
	return { m_transform, nullptr };
}

void EnemyGui::draw() {
	ImGui::Begin("Enemies");

	for (unsigned int i = 0; i < m_sprites.size(); ++i) {
		auto sprite = m_sprites[i]->m_sprite;

		auto uvX = sprite->getSpriteUvWidth();
		auto uvY = sprite->getSpriteUvHeight();
		auto offsetX = sprite->getSpriteUvXOffset();
		auto offsetY = sprite->getSpriteUvYOffset();

		if (ImGui::ImageButton((void*)(intptr_t)sprite->getTexture(), { 48, 48 }, { 0, 0 }, { float(uvX + offsetX), float(uvY + offsetY) })) {
			m_selection.m_type = SelectionType::Enemy;
			m_selection.m_id = m_sprites[i]->m_entity->getId();
			m_selection.m_index = i;
		}
		if (i == 0 || i % 5 != 0) {
			ImGui::SameLine();
		}
	}
	ImGui::End();
}