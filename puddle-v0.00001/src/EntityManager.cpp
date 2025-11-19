#include "EntityManager.h"

#include "TransformComponent.h"
#include "UnitComponent.h"
#include "SpriteComponent.h"

#include <iostream>
#include <sstream>

static const char ENTITY_FILE[] = "Data\\Entities\\entities.txt";
static const char ENTITY_SECTION[] = "Entity";
static const char TRANSFORM_SECTION[] = "Transform";
static const char SPRITE_SECTION[] = "Sprite";
static const char UNIT_SECTION[] = "Unit";

EntityManager::EntityManager() :
	_entities(200),
	_entities_cached(200)
{}

EntityManager::~EntityManager() {
	// let compact array delete entities/components
}

void EntityManager::update() {
	_components.update();
}

Entity* EntityManager::create(int id) {
	if (_entity_cache.find(id) == _entity_cache.end()) {
		load_cached_entity(id);
	}

	auto entity = _entities.get();
	auto& cached = _entity_cache.at(id);

	entity->set_id(cached.entity->get_id());


	for (int i = 0; i < entity->_components.size(); ++i) {
		if (cached.entity->_components[i] != nullptr) {
			bool attach = (entity->_components[i] == nullptr);
			switch (i) {
			case TRANSFORM_COMPONENT:
				if (attach) entity->attach(_components.get_transform());
				static_cast<TransformComponent*>(entity->_components[i])->copy(entity, *static_cast<TransformComponent*>(cached.entity->_components[i]));  // пиздец
				break;
			case UNIT_COMPONENT:
				if (attach) entity->attach(_components.get_unit());
				static_cast<UnitComponent*>(entity->_components[i])->copy(entity, *static_cast<UnitComponent*>(cached.entity->_components[i]));  // пиздец
				break;
			case SPRITE_COMPONENT:
				if (attach) entity->attach(_components.get_sprite());
				static_cast<SpriteComponent*>(entity->_components[i])->copy(entity, *static_cast<SpriteComponent*>(cached.entity->_components[i]));  // пиздец
				break;
			}
		}
		else if (cached.entity->_components[i] == nullptr && entity->_components[i] != nullptr) {
			switch (i) {
			case TRANSFORM_COMPONENT:
				_components.burn_transform(entity->get<TransformComponent>());
				break;
			case UNIT_COMPONENT:
				_components.burn_unit(entity->get<UnitComponent>());
				break;
			case SPRITE_COMPONENT:
				_components.burn_sprite(entity->get<SpriteComponent>());
				break;
			}
			entity->_components[i] = nullptr;
		}
	}

	++cached.ref_count;
	return entity;
}

void EntityManager::burn(Entity* entity) {
	auto& cached = _entity_cache.at(entity->get_id());
	if (--cached.ref_count == 0) {
		_components_cache.burn_entity_components(cached.entity);
		_entities_cached.remove(cached.entity);
		_entity_cache.erase(entity->get_id());
	}

	_components.burn_entity_components(entity);
	_entities.remove(entity);
	entity = nullptr;
}

std::string EntityManager::get_entity_file(int id) const {
	FileReader file(ENTITY_FILE, &FileReader::int_val);

	file.set_section(ENTITY_SECTION);
	std::string entity_file = "";
	file.read(&entity_file, id);

	return entity_file;
}

void EntityManager::load_cached_entity(int id) {
	std::string entity_file = get_entity_file(id);

	Cached cached;
	cached.entity = _entities_cached.get();
	cached.entity->set_id(id);
	cached.ref_count = 0;

	FileReader file(entity_file.c_str());
	file.set_section("Entity");

	std::string name = "";

	file.read(&name, "name");

	std::cout << "Loading: " << name << "\n";
	if (file.set_section(TRANSFORM_SECTION)) {
		loadTransform(file, cached.entity);
	}

	if (file.set_section(UNIT_SECTION)) {

	}

	if (file.set_section(SPRITE_SECTION)) {
		loadSprite(file, cached.entity);
	}

	_entity_cache.insert(std::pair<int, Cached>(id, cached));
}

void EntityManager::loadTransform(FileReader& file, Entity* entity) {
	auto transform = _components_cache.get_transform();

	file.read(&transform->_speed, "speed.f");
	float scale = 0.0f;
	file.read(&scale, "scale.f");
	transform->_scale = glm::vec2(scale, scale);

	entity->attach(transform);
}

void EntityManager::loadSprite(FileReader& file, Entity* entity) {
	auto sprite = _components_cache.get_sprite();

	file.set_section("Sprite");
	file.read(&sprite->_id, "id.i");
	file.read(&sprite->_shader, "shader.i");
	file.read(&sprite->_idle.begin, "idleBegin.i");
	file.read(&sprite->_idle.end, "idleEnd.i");

	entity->attach(sprite);
}

CompactArray<Entity>* EntityManager::getEntities() {
	return &_entities;
}

ComponentManager* EntityManager::get_component_manager() {
	return &_components;
}