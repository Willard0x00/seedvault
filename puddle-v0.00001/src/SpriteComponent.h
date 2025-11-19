#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Component.h"

#include <glm/gtc/matrix_transform.hpp>

struct FrameRange {
    uint8_t begin;
    uint8_t end;
};

enum Animation {
    OpIdle = 0x01,
};

struct SpriteComponent : public Component {
    SpriteComponent(Entity* entity = nullptr);

    void copy(Entity* const entity, const SpriteComponent& rhs);

    void update();

    glm::vec2 get_frame() const;

    static constexpr uint8_t _component_type = SPRITE_COMPONENT;

    int _id;
    int _shader;

    uint8_t _animation;
    uint8_t _frame;

    FrameRange _idle;
};

#endif