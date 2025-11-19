#include "SpriteManager.h"

#include "Log.h"
#include "Sprite.h"
#include "SpriteComponent.h"

#include <filesystem>

SpriteManager::SpriteManager() {
	const std::filesystem::path directory("Data\\Sprites\\");

	Log::get().write(L_SYSTEM, "Loading sprites");

	for (const auto& directoryEntry : std::filesystem::directory_iterator{ directory }) {
		if (directoryEntry.is_directory()) {
			for (const auto& subDirectoryEntry : std::filesystem::directory_iterator{ directoryEntry }) {
				if (subDirectoryEntry.is_regular_file() && subDirectoryEntry.path().extension() == ".json") {
					auto sprite = std::make_unique<Sprite>(subDirectoryEntry.path().string().c_str());
					m_sprites.insert(std::pair<uint16_t, std::unique_ptr<Sprite>>(sprite->getId(), std::move(sprite)));
				}
			}
		}
	}

	Log::get().write(L_SYSTEM, "Finished loading sprites");
}

SpriteManager::~SpriteManager() {

}

Sprite* SpriteManager::getSprite(uint16_t id) const {
	auto sprite = m_sprites.find(id);
	if (sprite != m_sprites.end()) {
		return sprite->second.get();
	}
	Log::get().write(L_ERROR, "Could not find sprite with id of: ", id);
	return nullptr;
}

void SpriteManager::linkSpriteToComponent(SpriteComponent* sprite) const {
	sprite->m_sprite = getSprite(sprite->m_id);
}
