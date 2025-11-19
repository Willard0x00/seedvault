#include "ComponentManager.h"

#include <iostream>

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ObjectComponent.h"
#include "AbilityComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"
#include "ItemComponent.h"

#include "Entity.h"

ComponentManager::ComponentManager() :
    m_transforms ( 3000 ),
    m_sprites ( 3000 ),
    m_objects ( 3000 ),
    m_abilities ( 3000 ),
    m_enemies ( 3000 ),
    m_players ( 10 ),
    m_items ( 3000 )
{}

void ComponentManager::update() {
    for (auto it = m_transforms.begin(); it != m_transforms.end(); ++it) {
        it->update();
    }

    for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it) {
        it->update();
    }

    for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
        it->update();
    }

    for (auto it = m_abilities.begin(); it != m_abilities.end(); ++it) {
        it->update();
    }

    for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it) {
        it->update();
    }

    for (auto it = m_players.begin(); it != m_players.end(); ++it) {
        it->update();
    }

    for (auto it = m_items.begin(); it != m_items.end(); ++it) {
        it->update();
    }
}

void ComponentManager::clear() {
    m_transforms.clear();
    m_sprites.clear();
    m_objects.clear();
    m_abilities.clear();
    m_enemies.clear();
    //m_players.clear();
    m_items.clear();
}

TransformComponent* ComponentManager::getTransform() {
    return m_transforms.get();
}

SpriteComponent* ComponentManager::getSprite() {
    return m_sprites.get();
}

ObjectComponent* ComponentManager::getObject() {
    return m_objects.get();
}

AbilityComponent* ComponentManager::getAbility() {
    return m_abilities.get();
}

EnemyComponent* ComponentManager::getEnemy() {
    return m_enemies.get();
}

PlayerComponent* ComponentManager::getPlayer() {
    return m_players.get();
}

ItemComponent* ComponentManager::getItem() {
    return m_items.get();
}

void ComponentManager::burnEntityComponents(Entity* entity) {
    if (auto transform = entity->get<TransformComponent>()) {
       m_transforms.remove(transform);
    }

    if (auto sprite = entity->get<SpriteComponent>()) {
        m_sprites.remove(sprite);
    }

    if (auto object = entity->get<ObjectComponent>()) {
        m_objects.remove(object);
    }

    if (auto ability = entity->get<AbilityComponent>()) {
        m_abilities.remove(ability);
    }

    if (auto enemy = entity->get<EnemyComponent>()) {
        m_enemies.remove(enemy);
    }

    if (auto player = entity->get<PlayerComponent>()) {
        //m_players.remove(player);
    }

    if (auto item = entity->get<ItemComponent>()) {
        m_items.remove(item);
    }
}

void ComponentManager::burnTransform(TransformComponent* transform) {
    m_transforms.remove(transform);
    transform = nullptr;
}

void ComponentManager::burnSprite(SpriteComponent* sprite) {
    m_sprites.remove(sprite);
    sprite = nullptr;
}

void ComponentManager::burnObject(ObjectComponent* object) {
    m_objects.remove(object);
    object = nullptr;
}

void ComponentManager::burnAbility(AbilityComponent* ability) {
    m_abilities.remove(ability);
    ability = nullptr;
}

void ComponentManager::burnEnemy(EnemyComponent* enemy) {
    m_enemies.remove(enemy);
    enemy = nullptr;
}

void ComponentManager::burnPlayer(PlayerComponent* player) {
    m_players.remove(player);
    player = nullptr;
}

void ComponentManager::burnItem(ItemComponent* item) {
    m_items.remove(item);
    item = nullptr;
}

CompactArray<TransformComponent>& ComponentManager::getTransforms() {
    return m_transforms;
}

CompactArray<SpriteComponent>& ComponentManager::getSprites() {
    return m_sprites;
}

CompactArray<ObjectComponent>& ComponentManager::getObjects() {
    return m_objects;
}

CompactArray<AbilityComponent>& ComponentManager::getAbilities() {
    return m_abilities;
}

CompactArray<EnemyComponent>& ComponentManager::getEnemies() {
    return m_enemies;
}

CompactArray<PlayerComponent>& ComponentManager::getPlayers() {
    return m_players;
}

CompactArray<ItemComponent>& ComponentManager::getItems() {
    return m_items;
}