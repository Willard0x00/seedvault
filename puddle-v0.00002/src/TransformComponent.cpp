#include "TransformComponent.h"

#define NOMINMAX

#include <imgui.h>

#include <rapidjson/document.h>

#include "Entity.h"
#include "Sprite.h"
#include "SpriteComponent.h"

TransformComponent::TransformComponent() :
    Component ( nullptr ),
    m_position ( 0, 0, 0 ),
    m_scale ( 1, 1 ),
    m_rotation ( 0 ),
    m_speed ( 1.0f ),
    m_destination ( 0, 0, 0 ),
    m_direction ( 0, 0, 0 ),
    m_hasDestination ( false ),
    m_isTraveling ( false ),
    m_skipFirstTravel ( false ),
    m_width ( 0 ),
    m_height ( 0 )
{}

void TransformComponent::copy(Entity* const entity, const TransformComponent& rhs) {
    m_entity = entity;
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    m_speed = rhs.m_speed;
    m_destination = rhs.m_destination;
    m_direction = rhs.m_direction;
    m_hasDestination = rhs.m_hasDestination;
    m_isTraveling = rhs.m_isTraveling;
    m_skipFirstTravel = rhs.m_skipFirstTravel;
    m_width = rhs.m_width;
    m_height = rhs.m_height;
}

void TransformComponent::clear() {
    m_entity = nullptr;
    m_position = glm::vec3(0, 0, 0);
    m_scale = glm::vec2(1, 1);
    m_rotation = 0.0f;
    m_speed = 1.0f;
    m_destination = glm::vec3(0, 0, 0);
    m_direction = glm::vec3(0, 0, 0);
    m_hasDestination = false;
    m_isTraveling = false;
    m_skipFirstTravel = false;
    m_width = 0;
    m_height = 0;
}

void TransformComponent::update() {
    if (m_hasDestination) {
        glm::vec3 dir = glm::normalize(m_destination - m_position);

        direction(dir.x, 0);

        m_position += dir * m_speed * 0.0001f;

        if (m_position == m_destination) {
            m_hasDestination = false;
        }
    }
    else if (m_isTraveling) {
        if (m_skipFirstTravel) {
            m_skipFirstTravel = false;
            return;
        }
        m_position += m_direction * m_speed * 0.0001f;
    }
}

void TransformComponent::load(Entity* entity, void* document) {
    this->clear();

    auto& doc = *static_cast<rapidjson::Value*>(document);

    m_speed = doc["speed"].GetFloat();

    if (doc.HasMember("scale")) {
        glm::vec2 scale;
        scale.x = doc["scale"].GetArray()[0].GetFloat();
        scale.y = doc["scale"].GetArray()[1].GetFloat();
        m_scale = scale;
    }

    if (doc.HasMember("rotation")) {
        m_rotation = doc["rotation"].GetFloat();
    }

    if (doc.HasMember("position")) {
        glm::vec3 position;
        position.x = doc["position"].GetArray()[0].GetFloat();
        position.y = doc["position"].GetArray()[1].GetFloat();
        position.z = doc["position"].GetArray()[2].GetFloat();
        m_position = position;
    }

    if (doc.HasMember("width")) {
        m_width = doc["width"].GetInt();
    }

    if (doc.HasMember("height")) {
        m_height = doc["height"].GetInt();
    }

    entity->attach(this);
}

void TransformComponent::save(void* p_document, void* p_allocator) {
    auto& document = *static_cast<rapidjson::Document*>(p_document);
    auto& allocator = *static_cast<rapidjson::Document::AllocatorType*>(p_allocator);

    rapidjson::Value transformDoc;
    transformDoc.SetObject();
    transformDoc.AddMember("speed", rapidjson::Value(m_speed), allocator);

    rapidjson::Value positionValue(rapidjson::kArrayType);
    positionValue.PushBack(m_position[0], allocator);
    positionValue.PushBack(m_position[1], allocator);
    positionValue.PushBack(m_position[2], allocator);
    transformDoc.AddMember("position", positionValue, allocator);

    rapidjson::Value scaleValue(rapidjson::kArrayType);
    scaleValue.PushBack(m_scale[0], allocator);
    scaleValue.PushBack(m_scale[1], allocator);
    transformDoc.AddMember("scale", scaleValue, allocator);

    transformDoc.AddMember("rotation", rapidjson::Value(m_rotation), allocator);

    transformDoc.AddMember("width", rapidjson::Value(m_width), allocator);
    transformDoc.AddMember("height", rapidjson::Value(m_height), allocator);

    document.AddMember("Transform", transformDoc, allocator);
}

void TransformComponent::move(uint8_t dir, float dt) {
    m_hasDestination = false;

    const bool y = dir & OpUp || dir & OpDown;
    const bool x = dir & OpLeft || dir & OpRight;

    const float distance = m_speed * dt;
    glm::vec3 vector = glm::normalize(glm::vec3((x) ? 1.0f : 0.0f, (y) ? 1.0f : 0.0f, 0.0f)) * distance;

    if (dir & OpUp) {
        m_position.y -= vector.y;
    }

    if (dir & OpDown) {
        m_position.y += vector.y;
    }

    if (dir & OpLeft) {
        m_position.x -= vector.x;
    }

    if (dir & OpRight) {
        m_position.x += vector.x;
    }

    if (dir & OpRRight) {
        m_rotation += distance + 1.0f;
    }

    if (dir & OpRLeft) {
        m_rotation -= distance + 1.0f;
    }
}

void TransformComponent::direction(double x, double y) {
    m_scale.x = (x < 0.5) ? -abs(m_scale.x) : abs(m_scale.x);
}

void TransformComponent::setDestination(glm::vec3 destination) {
    m_destination = destination;

    m_hasDestination = true;
    m_isTraveling = false;
    m_skipFirstTravel = true;
}

void TransformComponent::setTravel(glm::vec3 direction) {
    m_direction = glm::normalize(direction);

    m_hasDestination = false;
    m_isTraveling = true;
    m_skipFirstTravel = true;
}

#include "Log.h"
bool TransformComponent::collidesWith(glm::vec4 rect, bool perPixel) const {
    float width = m_width * m_scale.x;
    float height = m_height * m_scale.y;
    float x = m_position.x - width / 2.0f;
    float y = m_position.y - height / 2.0f;

    if (x >= rect.x + rect.z || x + width <= rect.x || y >= rect.y + rect.w || y + height <= rect.y) {
        return false;
    }

    if (!perPixel) {
        return true;
    }

    int left = (int)glm::max(x, rect.x);
    int right = (int)glm::min(x + width, rect.x + rect.z);
    int bottom = (int)glm::max(y, rect.y);
    int top = (int)glm::min(y + height, rect.y + rect.w);
    int columns = right - left + 1;
    int rows = top - bottom + 1;
    int aLeft = left - (int)x;
    int aBottom = bottom - (int)y;
    aLeft /= m_scale.x;
    aBottom /= m_scale.y;


    if (auto sprite = m_entity->get<SpriteComponent>()) {
        auto mask = sprite->m_sprite->getAlphaMask(sprite->m_frame.m_frame);
        int spriteWidth = sprite->m_sprite->getSpriteWidth();
        int spriteSize = sprite->m_sprite->getSpriteSize();
        if (mask) {
            for (int y = 0; y < rows; ++y) {
                for (int x = 0; x < columns; ++x) {
                    int index = (aLeft + x) + (aBottom + y) * spriteWidth;

                    if (index < spriteSize && mask[index]) { 
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool TransformComponent::collidesWith(TransformComponent* other) const {
    float width = m_width * m_scale.x;
    float height = m_height * m_scale.y;
    float oWidth = other->m_width * other->m_scale.x;
    float oHeight = other->m_height * other->m_scale.y;
    float x = m_position.x - width / 2.0f;
    float y = m_position.y - height / 2.0f;
    float otherX = other->m_position.x - oWidth / 2.0f;
    float otherY = other->m_position.y - oHeight / 2.0f;

    return x < otherX + oWidth &&
        x + width > otherX &&
        y < otherY + oHeight &&
        y + height > otherY;
}

void TransformComponent::drawGuiTree() {
    if (ImGui::TreeNode(("Transform##" + std::to_string((unsigned long long)this)).c_str())) {
        ImGui::Text("Position");
        ImGui::DragFloat("x##P", &m_position[0]);
        ImGui::DragFloat("y##P", &m_position[1]);
        ImGui::DragFloat("z##P", &m_position[2]);
        ImGui::Text("Scale");
        ImGui::DragFloat("x##S", &m_scale[0]);
        ImGui::DragFloat("y##S", &m_scale[1]);
        ImGui::Text("Rotation");
        ImGui::DragFloat("x##R", &m_rotation, 1.0f, -360.0f, 360.0f);
        ImGui::DragFloat("Speed", &m_speed);
        ImGui::InputInt("Collidable Width", &m_width);
        ImGui::InputInt("Collidable Height", &m_height);
        ImGui::TreePop();
    }
}

glm::vec3 TransformComponent::getPosition() const {
    if (auto sprite = m_entity->get<SpriteComponent>()) {
        return m_position + sprite->m_frame.m_position;
    }
    return m_position;
}

glm::vec2 TransformComponent::getScale() const {
    if (auto sprite = m_entity->get<SpriteComponent>()) {
        return m_scale * sprite->m_frame.m_scale;
    }
    return m_scale;
}

float TransformComponent::getRotation() const {
    if (auto sprite = m_entity->get<SpriteComponent>()) {
        return m_rotation + sprite->m_frame.m_rotation;
    }
    return m_rotation;
}