#ifndef ENEMY_COMPONENT_H
#define ENEMY_COMPONENT_H

#include "Component.h"

struct EnemyComponent : public Component {
    EnemyComponent();

    void copy(Entity* const entity, const EnemyComponent& rhs);

    void clear();

    void update();

    void load(Entity* entity, void* document);

    void save(void* p_document, void* p_allocator);

    void drawGuiTree();

    static constexpr uint8_t m_component_type = ENEMY_COMPONENT;

};

#endif