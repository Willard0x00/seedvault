#include "ItemComponent.h"

#include <imgui.h>
#include <rapidjson/document.h>

#include "Entity.h"
#include "SpriteComponent.h"

ItemComponent::ItemComponent() :
    Component(nullptr),
    m_slot ( 0 ),
    m_equippedRotation ( 0.0f )
{}

void ItemComponent::copy(Entity* const entity, const ItemComponent& rhs) {
    m_entity = entity;
    m_slot = rhs.m_slot;
    m_equippedRotation = rhs.m_equippedRotation;
}

void ItemComponent::clear() {
    m_entity = nullptr;
    m_slot = 0;
    m_equippedRotation = 0.0f;
}

void ItemComponent::update() {

}

void ItemComponent::load(Entity* entity, void* document) {
    this->clear();

    auto& doc = *static_cast<rapidjson::Value*>(document);

    m_slot = doc["slot"].GetInt();
    
    if (doc.HasMember("equipped rotation")) {
        m_equippedRotation = doc["equipped rotation"].GetFloat();
    }

    entity->attach(this);
}

void ItemComponent::save(void* p_document, void* p_allocator) {
    auto& document = *static_cast<rapidjson::Document*>(p_document);
    auto& allocator = *static_cast<rapidjson::Document::AllocatorType*>(p_allocator);

    rapidjson::Value itemDoc;
    itemDoc.SetObject();

    itemDoc.AddMember("slot", rapidjson::Value(m_slot), allocator);
    itemDoc.AddMember("equipped rotation", rapidjson::ValidateErrorCode(m_equippedRotation), allocator);

    document.AddMember("Item", itemDoc, allocator);
}

void ItemComponent::drawGuiTree() {
    if (ImGui::TreeNode(("Item##" + std::to_string((unsigned long long)this)).c_str())) {
        ImGui::InputScalar("Slot", ImGuiDataType_U8, &m_slot);
        ImGui::DragFloat("Equipped Rotation", &m_equippedRotation);
        ImGui::TreePop();
    }
}

void ItemComponent::hide() {
    if (auto sprite = m_entity->get<SpriteComponent>()) {
        sprite->m_isVisible = false;
    }
}

void ItemComponent::show() {
    if (auto sprite = m_entity->get<SpriteComponent>()) {
        sprite->m_isVisible = true;
    }
}