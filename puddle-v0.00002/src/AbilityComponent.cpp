#include "AbilityComponent.h"

#include <imgui.h>
#include <rapidjson/document.h>

#include "Entity.h"

AbilityComponent::AbilityComponent() :
	Component ( nullptr ),
    m_onInitFn ( nullptr ),
    m_onUpdateFn ( nullptr ),
    m_onDeleteFn ( nullptr )
{}

void AbilityComponent::copy(Entity* const entity, const AbilityComponent& rhs) {
    m_entity = entity;
    m_onInitFn = rhs.m_onInitFn;
    m_onUpdateFn = rhs.m_onUpdateFn;
    m_onDeleteFn = rhs.m_onDeleteFn;
    m_onInitFnName = rhs.m_onInitFnName;
    m_onUpdateFnName = rhs.m_onUpdateFnName;
    m_onDeleteFnName = rhs.m_onDeleteFnName;
}

void AbilityComponent::clear() {
    m_entity = nullptr;
    m_onInitFn = nullptr;
    m_onUpdateFn = nullptr;
    m_onDeleteFn = nullptr;
    m_onInitFnName = "";
    m_onUpdateFnName = "";
    m_onDeleteFnName = "";
}

void AbilityComponent::update() {

}

void AbilityComponent::load(Entity* entity, void* document) {
    this->clear();

    auto& doc = *static_cast<rapidjson::Value*>(document);

    if (doc.HasMember("onInit")) {
        m_onInitFnName = doc["onInit"].GetString();
    }

    if (doc.HasMember("onUpdate")) {
        m_onUpdateFnName = doc["onUpdate"].GetString();
    }

    if (doc.HasMember("onDelete")) {
        m_onInitFnName = doc["onDelete"].GetString();
    }

    entity->attach(this);
}

void AbilityComponent::save(void* p_document, void* p_allocator) {
    auto& document = *static_cast<rapidjson::Document*>(p_document);
    auto& allocator = *static_cast<rapidjson::Document::AllocatorType*>(p_allocator);

    rapidjson::Value abilityDoc;
    abilityDoc.SetObject();
    
    abilityDoc.AddMember("onInit", rapidjson::Value(m_onInitFnName.c_str(), allocator), allocator);
    abilityDoc.AddMember("onUpdate", rapidjson::Value(m_onUpdateFnName.c_str(), allocator), allocator);
    abilityDoc.AddMember("onDelete", rapidjson::Value(m_onDeleteFnName.c_str(), allocator), allocator);

    document.AddMember("Ability", abilityDoc, allocator);
}

void AbilityComponent::drawGuiTree() {
    if (ImGui::TreeNode(("Ability##" + std::to_string((unsigned long long)this)).c_str())) {
        ImGui::TreePop();
    }
}