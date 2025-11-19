#include <string>
#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H

class player
{
private:
	static int x;
	static int y;
	static int i;
	static int j;
	static char symbol;
	static int worldNumber;
	static std::string name;
	static int level;
	static int exp;
	static int health;
	static int attack;
	static int speed;
	static int luck;
	static int defense;
	static int maxHealth;
	static int gold;
public:
	void setPlayer(int nx, int ny, char nsymbol, std::string nname, int nhealth, int nlevel, int nexp, int nattack, int nspeed, int nluck, int ndefense, int nmaxHealth, int ngold);
	void setPlayer(int nhealth, int nattack, int ndefense, int nspeed, int nluck);
	void revive();
	void setHealth(int nhealth);
	void setMaxHealth(int nhealth);
	void setSymbol(char nsymbol);
	void setName(std::string nname);
	void setLevel(int nlevel);
	void setExp(int nexp);
	void setAttack(int nattack);
	void setSpeed(int nspeed);
	void setLuck(int nluck);
	void setDefense(int ndefense);
	void addExp(int nexp);
	void setX(int nx);
	void setY(int ny);
	void setI(int ni);
	void setJ(int nj);
	void setWorldNumber(int x);
	void setGold(int ngold);
	void up();
	void down();
	void left();
	void right();
	int getX();
	int getY();
	int getI();
	int getJ();
	int getWorldNumber();
	char getSymbol();
	std::string getName();
	int getHealth();
	int getLevel();
	int getExp();
	int getAttack();
	int getSpeed();
	int getLuck();
	int getDefense();
	int getMaxHealth();
	int getGold();
};

#endif