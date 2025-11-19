#include "Selection.h"

#include "Entity.h"
#include "SpriteComponent.h"

const bool Selection::hasGrab() const {
	return m_cursorGrab.z != 0.0f && m_cursorGrab.w != 0.0f;
}

void Selection::clear() {
	m_type = SelectionType::NONE;
	m_id = -1;
	m_index = -1;
}

void Selection::clearGrab() {
	for (auto entity : m_entities) {
		if (auto sprite = entity->get<SpriteComponent>()) {
			sprite->m_highlight = false;
		}
	}
	m_entities.clear();
}