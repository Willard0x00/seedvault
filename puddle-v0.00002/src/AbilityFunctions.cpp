#include "AbilityFunctions.h"

#include "Log.h"

#include "Game.h"
#include "Entity.h"

#include "TransformComponent.h"

#define STANDARD_SPELL_INIT "StandardSpellInit"

const float g_pi = 3.14159f;

AbilityFunctions::AbilityFunctions()
{
	m_initFns.emplace(STANDARD_SPELL_INIT, std::bind(&AbilityFunctions::m_onInitFnStandardSpell, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
}

AbilityFunctions::~AbilityFunctions()
{}

void AbilityFunctions::linkAbiltyFunctionsToComponent(AbilityComponent* component) {
	auto onInitFn = m_initFns.find(component->m_onInitFnName);
	auto onUpdateFn = m_updateFns.find(component->m_onUpdateFnName);
	auto onDeleteFn = m_deleteFns.find(component->m_onDeleteFnName);

	if (onInitFn != m_initFns.end()) {
		component->m_onInitFn = onInitFn->second;
	}

	if (onUpdateFn != m_updateFns.end()) {
		component->m_onUpdateFn = onUpdateFn->second;
	}

	if (onDeleteFn != m_deleteFns.end()) {
		component->m_onDeleteFn = onDeleteFn->second;
	}
}

void AbilityFunctions::m_onInitFnStandardSpell(Game* game, Entity* caster, Entity* ability, double x, double y) {
	auto transform = ability->get<TransformComponent>();
	auto casterTransform = caster->get<TransformComponent>();

	auto direction = glm::vec3(x, y, 0) - casterTransform->m_position;

	transform->setTravel(direction);

	direction = glm::normalize(direction);
	transform->m_position = caster->get<TransformComponent>()->m_position + direction * glm::vec3(10, 10, 0);

	glm::vec3 xAxis = glm::vec3(1, 0, 0);

	float angle = (glm::atan(direction.y, direction.x) - glm::atan(0.0f, 1.0f)) * (180.0f / g_pi);

	transform->m_rotation = (angle + -44.0f);
}