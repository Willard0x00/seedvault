#include "EntityManager.h"

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>
#include <fstream>
#include <filesystem>

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ObjectComponent.h"
#include "AbilityComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"
#include "ItemComponent.h"

#include "Sprite.h"
#include "Log.h"

EntityManager::EntityManager(linkSpriteToComponentFn linkSpriteToComponentFn, linkAbilityFunctionsToComponentFn linkAbilityFunctionsToComponentFn) :
	m_linkSpriteToComponentFn ( linkSpriteToComponentFn ),
	m_linkAbilityFunctionsToComponentFn ( linkAbilityFunctionsToComponentFn ),
	m_entities		 ( 3000 ),
	m_entitiesCached ( 3000 )
{
	const std::filesystem::path directory("Data\\Entities\\");

	Log::get().write(L_SYSTEM, "Loading entities");

	for (const auto& directoryEntry : std::filesystem::directory_iterator{ directory }) {
		if (directoryEntry.is_regular_file()) {
			loadCachedEntity(directoryEntry.path().string().c_str());
		}

		if (directoryEntry.is_directory()) {
			for (const auto& subDirectoryEntry : std::filesystem::directory_iterator{ directoryEntry }) {
				if (subDirectoryEntry.is_regular_file()) {
					loadCachedEntity(subDirectoryEntry.path().string().c_str());
				}
			}
		}
	}

	m_player = create(0);

	Log::get().write(L_SYSTEM, "Finished loading entities");
}

EntityManager::~EntityManager() {
	// let compact array delete entities/components
}

void EntityManager::update() {
	m_components.update();
}

Entity* EntityManager::create(int id) {
	if (m_entityCache.find(id) == m_entityCache.end()) {
		Log::get().write(L_ERROR, "Could not find an entity with id of: ", id);
		assert(0);
	}

	auto entity = m_entities.get();
	auto& cached = m_entityCache.at(id);

	copy(entity, cached);

	return entity;
}

void EntityManager::burn(Entity* entity) {
	auto& cached = m_entityCache.at(entity->getId());

	m_components.burnEntityComponents(entity);
	m_entities.remove(entity);
	entity = nullptr;
}

void EntityManager::loadCachedEntity(const char* file) {
	Log::get().write(L_INFO, "Loading entity file -> ", file);

	std::ifstream fileStream(file);
	rapidjson::IStreamWrapper iStreamWrapper(fileStream);

	rapidjson::Document document;
	document.ParseStream(iStreamWrapper);

	if (document.HasParseError()) {
		Log::get().write(L_ERROR, document.GetParseError());
		return;
	}

	if (!document.HasMember("Entity")) {
		Log::get().write(L_ERROR, "Entity file: ", file, " has no member 'Entity'");
		return;
	}

	Entity* cached;
	cached = m_entitiesCached.get();
	cached->load(&document["Entity"]);

	if (document["Entity"].HasMember("Transform")) {
		const auto& transformDoc = document["Entity"]["Transform"];
		auto component = m_components.getTransform();
		component->load(cached, (void*)&transformDoc);
	}

	if (document["Entity"].HasMember("Sprite")) {
		const auto& spriteDoc = document["Entity"]["Sprite"];
		auto component = m_components.getSprite();
		component->load(cached, (void*)&spriteDoc);
		m_linkSpriteToComponentFn(component);
		//component->transition((uint8_t)AnimationType::IDLE);
		component->play((uint8_t)AnimationKey::IDLE);
	}

	if (document["Entity"].HasMember("Object")) {
		const auto& objectDoc = document["Entity"]["Object"];
		auto component = m_components.getObject();
		component->load(cached, (void*)&objectDoc);
	}

	if (document["Entity"].HasMember("Ability")) {
		const auto& abilityDoc = document["Entity"]["Ability"];
		auto component = m_components.getAbility();
		component->load(cached, (void*)&abilityDoc);
		m_linkAbilityFunctionsToComponentFn(component);
	}

	if (document["Entity"].HasMember("Enemy")) {
		const auto& enemyDoc = document["Entity"]["Enemy"];
		auto component = m_components.getEnemy();
		component->load(cached, (void*)&enemyDoc);
	}

	if (document["Entity"].HasMember("Player")) {
		const auto& playerDoc = document["Entity"]["Player"];
		auto component = m_components.getPlayer();
		component->load(cached, (void*)&playerDoc);
	}

	if (document["Entity"].HasMember("Item")) {
		const auto& itemDoc = document["Entity"]["Item"];
		auto component = m_components.getItem();
		component->load(cached, (void*)&itemDoc);
	}

	m_entityCache.insert(std::pair<int, Entity*>(cached->getId(), cached));
}

Entity* EntityManager::getPlayer() const {
	return m_player;
}

CompactArray<Entity>& EntityManager::getEntities() {
	return m_entities;
}

const CompactArray<Entity>& EntityManager::getEntityCache() const {
	return m_entitiesCached;
}

ComponentManager& EntityManager::getComponentManager() {
	return m_components;
}
  
void EntityManager::save(const char* p_file) {
	rapidjson::Document document;
	document.SetObject();

	for (auto it = ++m_entities.begin() /* + 1 dont save the player for now */; it != m_entities.end(); ++it) {
		rapidjson::Value values;
		values.SetObject();
		rapidjson::Value name(it->getName().c_str(), document.GetAllocator());
		rapidjson::Value type(it->getType().c_str(), document.GetAllocator());
		rapidjson::Value id(it->getId());
		values.AddMember("name", name, document.GetAllocator());
		values.AddMember("type", type, document.GetAllocator());
		values.AddMember("id", id, document.GetAllocator());

		if (auto transform = it->get<TransformComponent>()) {
			transform->save(&values, &document.GetAllocator());
		}

		if (auto sprite = it->get<SpriteComponent>()) {
			sprite->save(&values, &document.GetAllocator());
		}

		if (auto object = it->get<ObjectComponent>()) {
			object->save(&values, &document.GetAllocator());
		}

		if (auto ability = it->get<AbilityComponent>()) {
			ability->save(&values, &document.GetAllocator());
		}

		if (auto enemy = it->get<EnemyComponent>()) {
			enemy->save(&values, &document.GetAllocator());
		}

		if (auto player = it->get<PlayerComponent>()) {
			player->save(&values, &document.GetAllocator());
		}

		if (auto item = it->get<ItemComponent>()) {
			item->save(&values, &document.GetAllocator());
		}

		document.AddMember("Entity", values, document.GetAllocator());
	}

	FILE* file;
	std::string fileName = std::string(p_file) + ".json";
	fopen_s(&file, fileName.c_str(), "wb");
	char buffer[1024];
	rapidjson::FileWriteStream fileWriteStream(file, buffer, sizeof(buffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(fileWriteStream);
	writer.SetFormatOptions(rapidjson::kFormatSingleLineArray);
	document.Accept(writer);
	if (file) {
		fclose(file);
	}
}

void EntityManager::load(const char* p_file) {
	Log::get().write(L_INFO, "Loading entities from: ", p_file);

	clear();

	std::ifstream fileStream(p_file);
	if (!fileStream.is_open()) {
		Log::get().write(L_ERROR, "Couldn't find json file: ", p_file);
		return;
	}

	rapidjson::IStreamWrapper iStreamWrapper(fileStream);
	rapidjson::Document document;
	document.ParseStream(iStreamWrapper);

	if (document.HasParseError()) {
		Log::get().write(L_ERROR, "Error parsing json file", document.GetParseError());
		return;
	}

	for (auto it = document.MemberBegin(); it != document.MemberEnd(); ++it) {
		if (strcmp(it->name.GetString(), "Entity") == 0) {
			Entity* entity = m_entities.get();
			entity->load(&it->value);

			if (it->value.HasMember("Transform")) {
				const auto& transformDoc = it->value["Transform"];
				auto component = m_components.getTransform();
				component->load(entity, (void*)&transformDoc);
			}

			if (it->value.HasMember("Sprite")) {
				const auto& spriteDoc = it->value["Sprite"];
				auto component = m_components.getSprite();
				component->load(entity, (void*)&spriteDoc);
				m_linkSpriteToComponentFn(component);
				component->play((uint8_t)AnimationKey::IDLE);
			}

			if (it->value.HasMember("Object")) {
				const auto& objectDoc = it->value["Object"];
				auto component = m_components.getObject();
				component->load(entity, (void*)&objectDoc);
			}

			if (it->value.HasMember("Ability")) {
				const auto& abilityDoc = it->value["Ability"];
				auto component = m_components.getAbility();
				component->load(entity, (void*)&abilityDoc);
				m_linkAbilityFunctionsToComponentFn(component);
			}

			if (it->value.HasMember("Enemy")) {
				const auto& enemyDoc = it->value["Enemy"];
				auto component = m_components.getEnemy();
				component->load(entity, (void*)&enemyDoc);
			}

			if (it->value.HasMember("Player")) {
				const auto& playerDoc = it->value["Player"];
				auto component = m_components.getPlayer();
				component->load(entity, (void*)&playerDoc);
			}

			if (it->value.HasMember("Item")) {
				const auto& itemDoc = it->value["Item"];
				auto component = m_components.getItem();
				component->load(entity, (void*)&itemDoc);
			}
		}
	}

	Log::get().write(L_INFO, "Finished loading entities");
}

void EntityManager::remove(Entity* p_entity) {
	m_entities.remove(p_entity);
}

Entity* EntityManager::duplicate(Entity* p_entity) {
	Entity* entity = m_entities.get();

	copy(entity, p_entity);

	return entity;
}

// copy from other to entity
// reusing the same pool of memory so cleaing old memory and setting
// the entity values the same as the cached values
// loop over components to create if the cached entity has the same type
// attach a new component to the entity and copy the cached component values
void EntityManager::copy(Entity* p_to, Entity* p_from) {
	p_to->setId(p_from->getId());
	p_to->setName(p_from->getName());
	p_to->setType(p_from->getType());

	for (unsigned int componentItr = 0; componentItr < p_from->m_components.size(); ++componentItr) {
		if (p_from->m_components[componentItr] != nullptr) {
			bool attach = (p_to->m_components[componentItr] == nullptr);
			switch (componentItr) {
			case TRANSFORM_COMPONENT:
				if (attach) p_to->attach(m_components.getTransform());
				static_cast<TransformComponent*>(p_to->m_components[componentItr])->copy(p_to, *static_cast<TransformComponent*>(p_from->m_components[componentItr]));  // пиздец
				break;
			case SPRITE_COMPONENT:
				if (attach) p_to->attach(m_components.getSprite());
				static_cast<SpriteComponent*>(p_to->m_components[componentItr])->copy(p_to, *static_cast<SpriteComponent*>(p_from->m_components[componentItr]));
				break;
			case OBJECT_COMPONENT:
				if (attach) p_to->attach(m_components.getObject());
				static_cast<ObjectComponent*>(p_to->m_components[componentItr])->copy(p_to, *static_cast<ObjectComponent*>(p_from->m_components[componentItr]));
				break;
			case ABILITY_COMPONENT:
				if (attach) p_to->attach(m_components.getAbility());
				static_cast<AbilityComponent*>(p_to->m_components[componentItr])->copy(p_to, *static_cast<AbilityComponent*>(p_from->m_components[componentItr]));
				break;
			case ENEMY_COMPONENT:
				if (attach) p_to->attach(m_components.getEnemy());
				static_cast<EnemyComponent*>(p_to->m_components[componentItr])->copy(p_to, *static_cast<EnemyComponent*>(p_from->m_components[componentItr]));
				break;
			case PLAYER_COMPONENT:
				if (attach) p_to->attach(m_components.getPlayer());
				static_cast<PlayerComponent*>(p_to->m_components[componentItr])->copy(p_to, *static_cast<PlayerComponent*>(p_from->m_components[componentItr]));
				break;
			case ITEM_COMPONENT:
				if (attach) p_to->attach(m_components.getItem());
				static_cast<ItemComponent*>(p_to->m_components[componentItr])->copy(p_to, *static_cast<ItemComponent*>(p_from->m_components[componentItr]));
				break;
			}
		}
		else if (p_from->m_components[componentItr] == nullptr && p_to->m_components[componentItr] != nullptr) {
			switch (componentItr) {
			case TRANSFORM_COMPONENT:
				m_components.burnTransform(p_to->get<TransformComponent>());
				break;
			case SPRITE_COMPONENT:
				m_components.burnSprite(p_to->get<SpriteComponent>());
				break;
			case OBJECT_COMPONENT:
				m_components.burnObject(p_to->get<ObjectComponent>());
				break;
			case ABILITY_COMPONENT:
				m_components.burnAbility(p_to->get<AbilityComponent>());
				break;
			case ENEMY_COMPONENT:
				m_components.burnEnemy(p_to->get<EnemyComponent>());
				break;
			case PLAYER_COMPONENT:
				m_components.burnPlayer(p_to->get<PlayerComponent>());
				break;
			case ITEM_COMPONENT:
				m_components.burnItem(p_to->get<ItemComponent>());
				break;
			}
			p_to->m_components[componentItr] = nullptr;
		}
	}
}

void EntityManager::clear() {
	// dont clear the player at the first index
	for (auto it = ++m_entities.begin(); it != m_entities.end(); ++it) {
		m_components.burnEntityComponents(*it);
	}
	m_entities.clearAllButFirst();
}