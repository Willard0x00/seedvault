#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"

#include <glm/gtc/matrix_transform.hpp>

typedef unsigned long long ULONGLONG;

enum Direction {
    OpUp = 0x01,
    OpDown = 0x02,
    OpLeft = 0x04,
    OpRight = 0x08,
    OpRRight = 0x10,
    OpRLeft = 0x20
};

struct TransformComponent : public Component {
    TransformComponent(Entity* entity = nullptr, glm::vec2 position = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1), float rotation = 0.0f);

    void copy(Entity* const entity, const TransformComponent& rhs);

    void update();

    void move(uint8_t dir, float dt = 1.0f);

    static constexpr uint8_t _component_type = TRANSFORM_COMPONENT;

    glm::mat4 get_model() const;

    glm::vec2 _position;
    glm::vec2 _scale;
    float _rotation;

    float _speed;
};

#endif
