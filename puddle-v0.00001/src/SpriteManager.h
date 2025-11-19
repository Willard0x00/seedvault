#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <map>

#include "Sprite.h"
#include "FileReader.h"

class SpriteManager {
public:
	SpriteManager();

	~SpriteManager();

	Sprite* get(int id) const;
private:
	void load(int id, std::string_view path);

	std::map<int, Sprite*> m_sprites;
};

#endif