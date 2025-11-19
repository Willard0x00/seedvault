#include <string>


#ifndef ITEM_H
#define ITEM_H

class item
{

private:
	bool equip;
	std::string name;
	int health;
	int attack;
	int defense;
	int speed;
	int luck;
	int use;
public:
	void setItem(std::string nname, int nhealth, int nattack, int ndefense, int nspeed, int nluck, int nuse);
	void setEquip(bool nequip);
	std::string getName();
	bool getEquip();
	int getHealth();
	int getAttack();
	int getDefense();
	int getSpeed();
	int getLuck();

};
#endif