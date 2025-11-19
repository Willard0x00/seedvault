#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>

#include "CompactArrayElement.h"

class Entity;

enum {
    TRANSFORM_COMPONENT,
    SPRITE_COMPONENT,
    OBJECT_COMPONENT,
    ABILITY_COMPONENT,
    ENEMY_COMPONENT,
    PLAYER_COMPONENT,
    ITEM_COMPONENT,
    TOTAL_COMPONENTS
};

struct Component : public CompactArrayElement {
    Component(Entity* entity) :
        m_entity(entity)
    {}

    virtual void clear() = 0;

    virtual void update() = 0;

    virtual void load(Entity* entity, void* document) = 0;

    virtual void drawGuiTree() = 0;

    Entity* m_entity;
};

#endif