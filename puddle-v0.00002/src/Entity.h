#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "CompactArrayElement.h"

#include <array>
#include <cassert>
#include <string>

class ComponentManager;

class Entity : public CompactArrayElement {
public:
    Entity();

    ~Entity();

    Entity& operator=(const Entity& rhs) = delete;

    Entity(const Entity&& rhs) = delete;

    template<typename _Component>
    void attach(_Component* component) {
        assert(component);
        component->m_entity = this;
        m_components[component->m_component_type] = component;
    }

    template<typename _Component>
    _Component* get() {
        return (_Component*)m_components[_Component::m_component_type];
    }

    void load(void* document);

    int getId() const;

    void setId(int id);

    std::string getName() const;

    void setName(const std::string& name);

    std::string getType() const;

    void setType(const std::string& type);

    void drawGuiTree();

    std::array<Component*, TOTAL_COMPONENTS> m_components{ nullptr };
private:
    int m_id;

    std::string m_name;
    std::string m_type;
};

#endif