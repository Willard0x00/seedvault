#ifndef ABILITY_FUNCTIONS_H
#define ABILITY_FUNCTIONS_H

#include <functional>
#include <map>
#include <string>

#include "AbilityComponent.h"

class Game;

class AbilityFunctions {
public:
	AbilityFunctions();
	~AbilityFunctions();

	void linkAbiltyFunctionsToComponent(AbilityComponent* component);
private:
	std::map<std::string, onInitFn> m_initFns;
	std::map<std::string, onUpdateFn> m_updateFns;
	std::map<std::string, onDeleteFn> m_deleteFns;

	void m_onInitFnStandardSpell(Game* game, Entity* caster, Entity* ability, double x, double y);

	void m_onUpdateFnStandardSpell(Game* game, Entity* entity);

	void m_onDeleteFnStandardSpell(Game* game, Entity* entity);
};

#endif