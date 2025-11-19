#include "PlayerComponent.h"

#include <imgui.h>
#include <rapidjson/document.h>

#include "Entity.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ItemComponent.h"

constexpr float g_toDegrees = 180.0f / 3.14159f;
static const glm::vec3 g_weaponOffset = glm::vec3(10, 10, 0);
static const float g_aTanX = glm::atan(0.0f, 1.0f);

PlayerComponent::PlayerComponent() :
    Component(nullptr)
{}

void PlayerComponent::copy(Entity* const entity, const PlayerComponent& rhs) {
    m_entity = entity;
}

void PlayerComponent::clear() {
    m_entity = nullptr;
}

void PlayerComponent::update() {
    if (auto weapon = m_inventory.getWeapon()) {

    }
}

void PlayerComponent::load(Entity* entity, void* document) {
    this->clear();

    auto& doc = *static_cast<rapidjson::Value*>(document);

    entity->attach(this);
}

void PlayerComponent::save(void* p_document, void* p_allocator) {
    auto& document = *static_cast<rapidjson::Document*>(p_document);
    auto& allocator = *static_cast<rapidjson::Document::AllocatorType*>(p_allocator);

    rapidjson::Value enemyDoc;
    enemyDoc.SetObject();

    document.AddMember("Player", enemyDoc, allocator);
}

void PlayerComponent::drawGuiTree() {
    if (ImGui::TreeNode(("Player##" + std::to_string((unsigned long long)this)).c_str())) {
        ImGui::TreePop();
    }
}

void PlayerComponent::setWeaponDirection(glm::vec3 worldPos) {
    if (auto weapon = m_inventory.getWeapon()) {
        if (auto transform = weapon->m_entity->get<TransformComponent>()) {
            glm::vec3 playerPosition = m_entity->get<TransformComponent>()->m_position;
            glm::vec3 direction = glm::normalize(worldPos - playerPosition);

            transform->m_position = playerPosition + direction * g_weaponOffset;
            float angle = (glm::atan(direction.y, direction.x) - g_aTanX) * g_toDegrees;

            transform->m_rotation = (angle + weapon->m_equippedRotation);

            if (auto sprite = weapon->m_entity->get<SpriteComponent>()) {
                sprite->m_animationInterpolator.setDirection(direction);
            }
        }
    }
}

void PlayerComponent::attack() {
    if (auto weapon = m_inventory.getWeapon()) {
        if (auto sprite = weapon->m_entity->get<SpriteComponent>()) {
            sprite->play((uint8_t)AnimationKey::ATTACK);
        }
    }
}