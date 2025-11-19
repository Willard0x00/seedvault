#include "EnemyComponent.h"

#include <imgui.h>
#include <rapidjson/document.h>

#include "Entity.h"

EnemyComponent::EnemyComponent() :
    Component(nullptr)
{}

void EnemyComponent::copy(Entity* const entity, const EnemyComponent& rhs) {
    m_entity = entity;
}

void EnemyComponent::clear() {
    m_entity = nullptr;
}

void EnemyComponent::update() {

}

void EnemyComponent::load(Entity* entity, void* document) {
    this->clear();

    auto& doc = *static_cast<rapidjson::Value*>(document);

    entity->attach(this);
}

void EnemyComponent::save(void* p_document, void* p_allocator) {
    auto& document = *static_cast<rapidjson::Document*>(p_document);
    auto& allocator = *static_cast<rapidjson::Document::AllocatorType*>(p_allocator);

    rapidjson::Value enemyDoc;
    enemyDoc.SetObject();

    document.AddMember("Enemy", enemyDoc, allocator);
}

void EnemyComponent::drawGuiTree() {
    if (ImGui::TreeNode(("Enemy##" + std::to_string((unsigned long long)this)).c_str())) {
        ImGui::TreePop();
    }
}