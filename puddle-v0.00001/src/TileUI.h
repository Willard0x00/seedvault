#ifndef TILE_UI_H
#define TILE_UI_H

#include <vector>

typedef unsigned int GLuint;

class TileUI {
public:
	TileUI();
	~TileUI();

	void draw();

	std::vector<GLuint> m_tiles;
	GLuint m_selected;
};

#endif