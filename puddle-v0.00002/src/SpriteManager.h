#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <map>
#include <memory>
#include <cstdint>

class Sprite;
struct SpriteComponent;

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();

	Sprite* getSprite(uint16_t id) const;

	void linkSpriteToComponent(SpriteComponent* sprite) const;
private:
	std::map<uint16_t, std::unique_ptr<Sprite>> m_sprites;
};

#endif