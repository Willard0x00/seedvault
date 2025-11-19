#ifndef ENTITY_TREE_GUI_H
#define ENTITY_TREE_GUI_H

#include "Selection.h"
#include <functional>

typedef std::function<void(Entity*)> removeEntityFn;
typedef std::function<Entity* (Entity*)> duplicateEntityFn;

struct EntityTreeGui {
	EntityTreeGui(Selection& selection, removeEntityFn removeEntityFn, duplicateEntityFn duplicateEntityFn);
	~EntityTreeGui();

	void draw();

	Selection& m_selection;

	removeEntityFn m_removeEntityFn;

	duplicateEntityFn m_duplicateEntityFn;
};

#endif
