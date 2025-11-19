#include "item.h"

void item::setItem( std::string nname, int nhealth, int nattack, int ndefense, int nspeed, int nluck, int nuse)
{
	name = nname;
	health = nhealth;
	attack = nattack;
	defense = ndefense;
	speed = nspeed;
	luck = nluck;
	use = nuse;
}

void item::setEquip(bool nequip) { equip = nequip; }
std::string item::getName() { return name; }
bool item::getEquip() { return equip; }
int item::getHealth() { return health; }
int item::getAttack() { return attack; }
int item::getDefense() { return defense; }
int item::getSpeed() { return speed; }
int item::getLuck() { return luck; }