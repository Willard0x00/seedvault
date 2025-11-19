#include "enemy.h"

void enemy::setEnemy(std::string nname, int nlevel, int nexp, int nhealth, int nattack, int nspeed, int nluck, int ndefense, int nitem, int nid)
{
	name = nname;
	level = nlevel;
	exp = nexp;
	health = nhealth;
	attack = nattack;
	speed = nspeed;
	luck = nluck;
	defense = ndefense;
	item = nitem;
	id = nid;
}

void enemy::setHealth(int nhealth) { health = nhealth; }
void enemy::setSpace(std::string s) { space = s; }
std::string enemy::getName() { return name; }
int enemy::getLevel() { return level; }
int enemy::getExp() { return exp; }
int enemy::getHealth() { return health; }
int enemy::getAttack() { return attack; }
int enemy::getLuck() { return luck; }
int enemy::getSpeed() { return speed; }
int enemy::getDefense() { return defense; }
int enemy::getItem() { return item; }
int enemy::getid() { return id; }
std::string enemy::getSpace() { return space; }