#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"

#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

enum Direction {
    OpUp = 0x01,
    OpDown = 0x02,
    OpLeft = 0x04,
    OpRight = 0x08,
    OpRRight = 0x10,
    OpRLeft = 0x20
};

struct TransformComponent : public Component {
    TransformComponent();

    void copy(Entity* const entity, const TransformComponent& rhs);

    void clear();

    void update();
    
    void load(Entity* entity, void* document);

    void save(void* p_document, void* allocator);

    void move(uint8_t dir, float dt = 1.0f);

    void direction(double x, double y);

    void setDestination(glm::vec3 destination);

    void setTravel(glm::vec3 direction);

    bool collidesWith(glm::vec4 rect, bool perPixel) const;

    bool collidesWith(TransformComponent* transform) const;

    void drawGuiTree();

    glm::vec3 getPosition() const;

    glm::vec2 getScale() const;

    float getRotation() const;

    static constexpr uint8_t m_component_type = TRANSFORM_COMPONENT;

    glm::vec3 m_position;
    glm::vec2 m_scale;
    float m_rotation;

    int m_width;
    int m_height;

    float m_speed;

    glm::vec3 m_destination;
    glm::vec3 m_direction;

    bool m_hasDestination;
    bool m_isTraveling;
    bool m_skipFirstTravel;
};

#endif
