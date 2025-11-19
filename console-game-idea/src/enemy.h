#include <string>

#ifndef ENEMY_H
#define ENEMY_H

class enemy
{
private:
	std::string name;
	int level;
	int exp;
	int health;
	int attack;
	int speed;
	int luck;
	int defense;
	int item;
	int id;
	std::string space;
public:
	void setEnemy(std::string nname, int nlevel, int nexp, int nhealth, int nattack, int nspeed, int nluck, int ndefense, int nitem, int id);
	void setHealth(int nhealth);
	void setSpace(std::string s);
	std::string getName();
	int getLevel();
	int getExp();
	int getHealth();
	int getAttack();
	int getSpeed();
	int getLuck();
	int getDefense();
	int getItem();
	int getid();
	std::string getSpace();
};

#endif