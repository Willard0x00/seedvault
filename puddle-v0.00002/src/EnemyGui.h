#ifndef ENEMY_GUI_H
#define ENEMY_GUI_H

#include <vector>

#include "CompactArray.h"
#include "Entity.h"
#include "Transform.h"
#include "Selection.h"

struct SpriteComponent;

struct EnemyCursor {
	const Transform& transform;
	SpriteComponent* sprite;
};

struct EnemyGui {
	EnemyGui(Selection& selection, const CompactArray<Entity>& entities);
	~EnemyGui();

	void setCursor(double x, double y);

	void draw();

	EnemyCursor getCursor() const;

	std::vector<SpriteComponent*> m_sprites;

	Selection& m_selection;

	Transform m_transform;
};

#endif