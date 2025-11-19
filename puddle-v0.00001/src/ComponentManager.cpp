#include "ComponentManager.h"

#include <iostream>

#include "TransformComponent.h"
#include "UnitComponent.h"
#include "SpriteComponent.h"

#include "Entity.h"

ComponentManager::ComponentManager() :
    _transform_components(200),
    _unit_components(200), // this needs to be extended
    _sprite_components(200)
{}

void ComponentManager::update() {
    for (auto it = _transform_components.begin(); it != _transform_components.end(); ++it) {
        it->update();
    }

    for (auto it = _unit_components.begin(); it != _unit_components.end(); ++it) {
        it->update();
    }

    for (auto it = _sprite_components.begin(); it != _sprite_components.end(); ++it) {
        it->update();
    }
}

TransformComponent* ComponentManager::get_transform() {
    return _transform_components.get();
}

UnitComponent* ComponentManager::get_unit() {
    return _unit_components.get();
}

SpriteComponent* ComponentManager::get_sprite() {
    return _sprite_components.get();
}

void ComponentManager::burn_entity_components(Entity* entity) {
    if (auto transform = entity->get<TransformComponent>()) {
        _transform_components.remove(transform);
    }

    if (auto unit = entity->get<UnitComponent>()) {
        _unit_components.remove(unit);
    }

    if (auto sprite = entity->get<SpriteComponent>()) {
        _sprite_components.remove(sprite);
    }
}

void ComponentManager::burn_transform(TransformComponent* transform) {
    _transform_components.remove(transform);
    transform = nullptr;
}

void ComponentManager::burn_unit(UnitComponent* unit) {
    _unit_components.remove(unit);
    unit = nullptr;
}

void ComponentManager::burn_sprite(SpriteComponent* sprite) {
    _sprite_components.remove(sprite);
    sprite = nullptr;
}

CompactArray<TransformComponent>* ComponentManager::get_transform_components() {
    return &_transform_components;
}