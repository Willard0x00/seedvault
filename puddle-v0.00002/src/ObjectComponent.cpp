#include "ObjectComponent.h"

#include "Entity.h"

#include <imgui.h>
#include <rapidjson/document.h>

ObjectComponent::ObjectComponent() :
    Component(nullptr)
{}

void ObjectComponent::copy(Entity* const entity, const ObjectComponent& rhs) {
    m_entity = entity;
}

void ObjectComponent::clear() {
    m_entity = nullptr;
}

void ObjectComponent::update() {
}

void ObjectComponent::load(Entity* entity, void* document) {
    this->clear();

    entity->attach(this);
}

void ObjectComponent::save(void* p_document, void* p_allocator) {
    auto& document = *static_cast<rapidjson::Document*>(p_document);
    auto& allocator = *static_cast<rapidjson::Document::AllocatorType*>(p_allocator);

    rapidjson::Value spriteDoc;
    spriteDoc.SetObject();

    document.AddMember("Object", spriteDoc, allocator);
}

void ObjectComponent::drawGuiTree() {
    if (ImGui::TreeNode(("Object##" + std::to_string((unsigned long long)this)).c_str())) {
        ImGui::TreePop();
    }
}