#ifndef MENU_GUI_H
#define MENU_GUI_H

#include <functional>
#include <string>

#include "CreateNewMapDialog.h"
#include "SpriteSheetDialog.h"

typedef std::function<void(CreateNewMapDialog)> NewMapFn;
typedef std::function<void(const char*)> SaveMapFn;
typedef std::function<void(const char*)> LoadMapFn;
typedef std::function<void(const char*)> SaveEntitiesFn;
typedef std::function<void(const char*)> LoadEntitiesFn;

struct MenuGui {
	MenuGui(NewMapFn newMapFn, SaveMapFn saveMapFn, LoadMapFn loadMapFn, SaveEntitiesFn saveEntitiesFn, LoadEntitiesFn loadEntitiesFn, const std::string* mapName);
	~MenuGui();

	void draw();

	void drawFile();

	void drawEdit();

	void popUp();

	NewMapFn m_newMapFn;

	SaveMapFn m_saveMapFn;

	LoadMapFn m_loadMapFn;

	SaveEntitiesFn m_saveEntitiesFn;

	LoadEntitiesFn m_loadEntitiesFn;

	const std::string* m_mapName;

	CreateNewMapDialog m_createNewMapDialog;

	SpriteSheetDialog m_spriteSheetDialog;

	bool m_openNewMapPopup;
	bool m_openLoadMapPopup;
	bool m_openSpriteSheetPopup;
};

#endif