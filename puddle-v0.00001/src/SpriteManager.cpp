#include "SpriteManager.h"

#include "FileReader.h"
#include "Program.h"
#include "Camera.h"

static const char SPRITE_FILE[] = "Data/Entities/sprites.txt";

SpriteManager::SpriteManager() {
	FileReader file(SPRITE_FILE, FileReader::int_val);

	file.set_section("Shaders");
	if (file.is_read()) {
		for (auto it = file.s_begin(); it != file.s_end(); ++it) {
			load(it->key_val, it->value);
		}
	}
}

SpriteManager::~SpriteManager() {
	for (auto it : m_sprites) {
		delete it.second;
	}
}

void SpriteManager::load(int id, std::string_view path) {
	Sprite* sprite = new Sprite(path);
	m_sprites.insert(std::pair<int, Sprite*>(id, sprite));
}

Sprite* SpriteManager::get(int id) const {
	const auto it = m_sprites.find(id);
	return (it != m_sprites.end()) ? it->second : nullptr;
}