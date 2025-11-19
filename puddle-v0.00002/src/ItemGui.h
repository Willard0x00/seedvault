#ifndef ITEM_GUI_H
#define ITEM_GUI_H

#include <vector>

#include "CompactArray.h"
#include "Entity.h"
#include "Transform.h"
#include "Selection.h"

struct SpriteComponent;

struct ItemCursor {
	const Transform& transform;
	SpriteComponent* sprite;
};

struct ItemGui {
	ItemGui(Selection& selection, const CompactArray<Entity>& entities);
	~ItemGui();

	void setCursor(double x, double y);

	void draw();

	ItemCursor getCursor() const;

	std::vector<SpriteComponent*> m_sprites;

	Selection& m_selection;

	Transform m_transform;
};

#endif