#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"
#include "Inventory.h"

struct PlayerComponent : public Component {
    PlayerComponent();

    void copy(Entity* const entity, const PlayerComponent& rhs);

    void clear();

    void update();

    void load(Entity* entity, void* document);

    void save(void* p_document, void* p_allocator);

    void drawGuiTree();

    void setWeaponDirection(glm::vec3 worldPos);

    void attack();

    static constexpr uint8_t m_component_type = PLAYER_COMPONENT;

    Inventory m_inventory;
};

#endif