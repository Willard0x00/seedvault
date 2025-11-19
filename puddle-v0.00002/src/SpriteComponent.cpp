#include "SpriteComponent.h"

#include <imgui.h>
#include <rapidjson/document.h>

#include "Sprite.h"

#include "Log.h"

#include "Entity.h"

#include "EngineClock.h"

SpriteComponent::SpriteComponent() :
	Component ( nullptr ),
    m_id ( 0 ),
    m_sprite ( nullptr ),
    m_animation ( nullptr ),
    m_animationInterpolator ( m_animation, &m_frame ),
    m_highlight ( false ),
    m_isVisible ( true)
{}

void SpriteComponent::copy(Entity* const entity, const SpriteComponent& rhs) {
    m_entity = entity;
    m_sprite = rhs.m_sprite;
    m_frame = rhs.m_frame;
    m_animation = rhs.m_animation;
    m_animationInterpolator.set(m_animation, &m_frame);
    m_id = rhs.m_id;
    m_highlight = rhs.m_highlight;
    m_isVisible = rhs.m_isVisible;
}

void SpriteComponent::clear() {
    m_entity = nullptr;
    m_sprite = nullptr;
    m_frame = Frame();
    m_animation = nullptr;
    m_id = 0;
    m_highlight = false;
    m_isVisible = true;
}

void SpriteComponent::update() {
    if (m_animation) {
        m_animationInterpolator.update();
    }
}

void SpriteComponent::load(Entity* entity, void* document) {
    this->clear();

    auto& doc = *static_cast<rapidjson::Value*>(document);

    m_id = doc["id"].GetInt();

    entity->attach(this);
}

void SpriteComponent::save(void* p_document, void* p_allocator) {
    auto& document = *static_cast<rapidjson::Document*>(p_document);
    auto& allocator = *static_cast<rapidjson::Document::AllocatorType*>(p_allocator);

    rapidjson::Value spriteDoc;
    spriteDoc.SetObject();

    spriteDoc.AddMember("id", rapidjson::Value(m_id), allocator);

    document.AddMember("Sprite", spriteDoc, allocator);
}

void SpriteComponent::play(uint8_t animationType) {
    if (m_sprite) {

        if (m_animation && (m_animation->m_type == animationType) && !m_animationInterpolator.isStopped()) {
            return;
        }

        switch (animationType) {
        case (uint8_t)AnimationKey::IDLE:
            m_animation = m_sprite->getAnimation((uint8_t)AnimationKey::IDLE);
            break;
        case (uint8_t)AnimationKey::ATTACK:
            m_animation = m_sprite->getAnimation((uint8_t)AnimationKey::ATTACK);
            break;
        default:
            m_animation = nullptr;
        }

        m_animationInterpolator.set(m_animation, &m_frame);
        m_animationInterpolator.start();
    }
}

void SpriteComponent::drawGuiTree() {
    if (ImGui::TreeNode(("Sprite##" + std::to_string((unsigned long long)this)).c_str())) {

        ImGui::Text("Animation");
        ImGui::TreePop();
    }
}