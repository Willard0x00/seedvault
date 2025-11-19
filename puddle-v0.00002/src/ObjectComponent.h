#ifndef OBJECT_COMPONENT_H
#define OBJECT_COMPONENT_H

#include "Component.h"

struct ObjectComponent : public Component {
    ObjectComponent();

    void copy(Entity* const entity, const ObjectComponent& rhs);

    void clear();

    void update();

    void load(Entity* entity, void* document);

    void save(void* p_document, void* p_allocator);

    void drawGuiTree();

    static constexpr uint8_t m_component_type = OBJECT_COMPONENT;
};

#endif