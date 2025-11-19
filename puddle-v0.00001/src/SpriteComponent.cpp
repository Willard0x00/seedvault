#include "SpriteComponent.h"

#include "PeriodicTimer.h"

SpriteComponent::SpriteComponent(
    Entity* entity) :
    Component(entity),
    _id        ( 0 ),
    _shader    ( 0 ),
    _animation ( 1 ),
    _frame     ( 0 ),
    _idle      ( { 0, 0 } )
{}

void SpriteComponent::copy(Entity* const entity, const SpriteComponent& rhs) {
    _entity = entity;
    _id = rhs._id;
    _shader = rhs._shader;
    _animation = rhs._animation;
    _frame = rhs._frame;
    _idle = rhs._idle;
}

void SpriteComponent::update() {
    static PeriodicTimer idle_timer(400);
    if (_animation & OpIdle) {
        if (idle_timer.alert()) {
            _frame++;
            if (_frame > _idle.end) {
                _frame = _idle.begin;
            }
        }
    }
}

glm::vec2 SpriteComponent::get_frame() const {
    return glm::vec2(_frame * 32, 32);
}