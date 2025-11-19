#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <map>

#include "Component.h"
#include "Timer.h"
#include "Animation.h"
#include "AnimationInterpolator.h"

class Sprite;

struct SpriteComponent : public Component {
    SpriteComponent();

    void copy(Entity* const entity, const SpriteComponent& rhs);

    void clear();

    void update();

    void load(Entity* entity, void* document);

    void save(void* p_document, void* p_allocator);

    void drawGuiTree();

    static constexpr uint8_t m_component_type = SPRITE_COMPONENT;

    void play(uint8_t animationKey);

    uint16_t m_id;

    Sprite* m_sprite;

    Frame m_frame;

    Animation* m_animation;

    AnimationInterpolator m_animationInterpolator;

    bool m_highlight;

    bool m_isVisible;
};

#endif