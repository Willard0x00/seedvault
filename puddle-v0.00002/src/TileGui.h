#ifndef TILE_GUI_H
#define TILE_GUI_H

#include <vector>

#include "Selection.h"

struct TileGui {
	TileGui(Selection& selection);
	~TileGui();

	void draw();

	std::vector<unsigned int> m_tiles;

	Selection& m_selection;
};

#endif