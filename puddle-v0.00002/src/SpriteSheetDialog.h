#ifndef SPRITE_SHEET_DIALOG_H
#define SPRITE_SHEET_DIALOG_H

#include <string>

struct SpriteSheetDialog {
	int m_sprites = 0;
	int m_padding = 2;
	int m_width = 0;
	int m_height = 0;
	std::string m_file = "Tools/";
};

#endif