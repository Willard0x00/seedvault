#ifndef OBJECT_GUI_H
#define OBJECT_GUI_H

#include <vector>

#include "CompactArray.h"
#include "Entity.h"
#include "Transform.h"
#include "Selection.h"

struct SpriteComponent;

struct ObjectCursor {
	const Transform& transform;
	SpriteComponent* sprite;
};

struct ObjectGui {
	ObjectGui(Selection& selection, const CompactArray<Entity>& entities);
	~ObjectGui();

	void setCursor(double x, double y);

	void draw();

	ObjectCursor getCursor() const;

	std::vector<SpriteComponent*> m_sprites;
	
	Selection& m_selection;

	Transform m_transform;
};

#endif