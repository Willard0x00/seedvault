#ifndef MENU_UI_H
#define MENU_UI_H

#include <functional>
#include <string>

class MenuUI {
public:
	MenuUI(std::function<void(std::string)> saveMapFn);
	~MenuUI();

	void draw();

	std::function<void(std::string)> m_saveMapFn;
};

#endif