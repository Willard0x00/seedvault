#ifndef CREATE_NEW_MAP_DIALOG_H
#define CREATE_NEW_MAP_DIALOG_H

#include <string>

struct CreateNewMapDialog {
	int width = 10;
	int height = 10;
	int tile = 0;
	std::string name = "Untitled";
};

#endif