#ifndef ITEM_COMPONENT_H
#define ITEM_COMPONENT_H

#include "Component.h"

struct ItemComponent : public Component {
    ItemComponent();

    void copy(Entity* const entity, const ItemComponent& rhs);

    void clear();

    void update();

    void load(Entity* entity, void* document);

    void save(void* p_document, void* p_allocator);

    void drawGuiTree();

    void hide();

    void show();

    static constexpr uint8_t m_component_type = ITEM_COMPONENT;

    uint8_t m_slot;

    float m_equippedRotation;
};

#endif