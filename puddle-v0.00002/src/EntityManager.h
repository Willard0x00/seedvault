#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "ComponentManager.h"
#include "CompactArray.h"

#include "Entity.h"

#include <string>
#include <map>
#include <memory>
#include <functional>

#include <rapidjson/document.h>

struct SpriteComponent;

typedef std::function<void(SpriteComponent*)> linkSpriteToComponentFn;
typedef std::function<void(AbilityComponent*)> linkAbilityFunctionsToComponentFn;

class EntityManager {
public:
	EntityManager(linkSpriteToComponentFn linkSpriteToComponentFn, linkAbilityFunctionsToComponentFn linkAbilityFunctionsToComponentFn);

	~EntityManager();

	void update();

	Entity* create(int id);

	void burn(Entity* entity);

	void loadCachedEntity(const char* file);

	ComponentManager& getComponentManager();

	CompactArray<Entity>& getEntities();

	const CompactArray<Entity>& getEntityCache() const;

	Entity* getPlayer() const;

	void save(const char* p_file);

	void load(const char* p_file);

	void remove(Entity* p_entity);

	Entity* duplicate(Entity* p_entity);

	void copy(Entity* p_to, Entity* p_from);

	void clear();
private:
	CompactArray<Entity> m_entities;
	ComponentManager m_components;

	CompactArray<Entity> m_entitiesCached;
	std::map<int, Entity*> m_entityCache;

	Entity* m_player;

	linkSpriteToComponentFn m_linkSpriteToComponentFn;
	linkAbilityFunctionsToComponentFn m_linkAbilityFunctionsToComponentFn;
};

#endif