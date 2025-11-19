#include "TransformComponent.h"

#include <iostream>
#include <Windows.h>

#include "Debug.h"

TransformComponent::TransformComponent(
    Entity* entity,
    glm::vec2 position,
    glm::vec2 scale,
    float rotation) :
    Component(entity),
    _position ( position ),
    _scale ( scale ),
    _rotation ( rotation ),
    _speed  ( 1.0f )
{}

void TransformComponent::copy(Entity* const entity, const TransformComponent& rhs) {
    _entity = entity;
    _position = rhs._position;
    _scale = rhs._scale;
    _rotation = rhs._rotation;
    _speed = rhs._speed;
}

void TransformComponent::update() {
}

void TransformComponent::move(uint8_t dir, float dt) {
    if (dir & OpUp) {
        _position.y -= (_speed * dt);
    }

    if (dir & OpDown) {
        _position.y += (_speed * dt);
    }

    if (dir & OpLeft) {
        _position.x -= (_speed * dt);
    }

    if (dir & OpRight) {
        _position.x += (_speed * dt);
    }

    if (dir & OpRRight) {
        _rotation += (_speed * dt);
    }

    if (dir & OpRLeft) {
        _rotation -= (_speed * dt);
    }
}

glm::mat4 TransformComponent::get_model() const {
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, glm::vec3(_position, 0.0f));
    m = glm::translate(m, glm::vec3(0.5f * _scale.x, 0.5f * _scale.y, 0.0f));
    m = glm::rotate(m, glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m = glm::translate(m, glm::vec3(-.5f * _scale.x, -.5f * _scale.y, 0.0f));
    m = glm::scale(m, glm::vec3(_scale, 1.0f));
    return m;
}