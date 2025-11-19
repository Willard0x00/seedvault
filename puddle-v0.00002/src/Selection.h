#ifndef SELECTION_H
#define SELECTION_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Entity;

enum class SelectionType {
	NONE,
	TILE,
	Object,
	Enemy,
	Item
};

struct Selection {
	SelectionType m_type = SelectionType::NONE;
	unsigned int m_id = 0;
	unsigned int m_index = 0;

	glm::vec4 m_cursorGrab;

	std::vector<Entity*> m_entities;

	bool m_isGrabbing = false;

	const bool hasGrab() const;

	void clear();

	void clearGrab();
};

#endif