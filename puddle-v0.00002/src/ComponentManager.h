#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "CompactArray.h"

class Entity;

struct TransformComponent;
struct SpriteComponent;
struct ObjectComponent;
struct AbilityComponent;
struct EnemyComponent;
struct PlayerComponent;
struct ItemComponent;

class ComponentManager {
public:
    ComponentManager();

    void update();

    void clear();

    TransformComponent* getTransform();

    SpriteComponent* getSprite();

    ObjectComponent* getObject();

    AbilityComponent* getAbility();

    EnemyComponent* getEnemy();

    PlayerComponent* getPlayer();

    ItemComponent* getItem();

    void burnEntityComponents(Entity* entity);

    void burnTransform(TransformComponent* transform);

    void burnSprite(SpriteComponent* sprite);

    void burnObject(ObjectComponent* object);

    void burnAbility(AbilityComponent* ability);

    void burnEnemy(EnemyComponent* enemy);

    void burnPlayer(PlayerComponent* player);

    void burnItem(ItemComponent* item);

    CompactArray<TransformComponent>& getTransforms();

    CompactArray<SpriteComponent>& getSprites();

    CompactArray<ObjectComponent>& getObjects();

    CompactArray<AbilityComponent>& getAbilities();

    CompactArray<EnemyComponent>& getEnemies();

    CompactArray<PlayerComponent>& getPlayers();;

    CompactArray<ItemComponent>& getItems();
private:
    CompactArray<TransformComponent> m_transforms;

    CompactArray<SpriteComponent> m_sprites;

    CompactArray<ObjectComponent> m_objects;

    CompactArray<AbilityComponent> m_abilities;

    CompactArray<EnemyComponent> m_enemies;

    CompactArray<PlayerComponent> m_players;

    CompactArray<ItemComponent> m_items;
};

#endif