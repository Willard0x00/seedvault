#ifndef ABILITY_COMPONENT_H
#define ABILITY_COMPONENT_H

#include "Component.h"

#include <functional>
#include <string>

class Ability;
class Game;

typedef std::function<void(Game*, Entity*, Entity*, double x, double y)> onInitFn;
typedef std::function<void(Game*, Entity*)> onUpdateFn;
typedef std::function<void(Game*, Entity* )> onDeleteFn;

struct AbilityComponent : public Component {
    AbilityComponent();

    void copy(Entity* const entity, const AbilityComponent& rhs);

    void clear();

    void update();

    void load(Entity* entity, void* document);

    void save(void* p_document, void* p_allocator);

    void drawGuiTree();

    static constexpr uint8_t m_component_type = ABILITY_COMPONENT;

    onInitFn m_onInitFn;
    onUpdateFn m_onUpdateFn;
    onDeleteFn m_onDeleteFn;

    std::string m_onInitFnName;
    std::string m_onUpdateFnName;
    std::string m_onDeleteFnName;
};

#endif