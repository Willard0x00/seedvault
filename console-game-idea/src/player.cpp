#include "player.h"

void player::setPlayer(int nx, int ny, char nsymbol, std::string nname, int nhealth, int nlevel, int nexp, int nattack, int nspeed, int nluck, int ndefense, int nmaxHealth, int ngold)
{
	x = nx;
	y = ny;
	symbol = nsymbol;
	name = nname;
	health = nhealth;
	level = nlevel;
	exp = nexp;
	attack = nattack;
	speed = nspeed;
	luck = nluck;
	defense = ndefense;
	maxHealth = nmaxHealth;
	gold = ngold;
}

void player::setPlayer(int nhealth, int nattack, int ndefense, int nspeed, int nluck)
{
	maxHealth = nhealth;
	attack = nattack;
	defense = ndefense;
	speed = nspeed;
	luck = nluck;
}

void player::addExp(int nexp)
{
	exp = exp + nexp;

	if (exp >= 100)
	{
		std::cout << "LEVEL UP!" << std::endl;
		std::cout << "You gain +10 Health" << std::endl;
		std::cout << "You gain +1 Attack" << std::endl;
		std::cout << "You gain +1 Defense" << std::endl;

		level++;
		attack++;
		defense++;
		exp = exp - 100;
		maxHealth = (maxHealth + 10);
		health = maxHealth;
	}
}

void player::revive() { health = maxHealth; }
void player::setHealth(int nhealth) { health = nhealth; }
void player::setMaxHealth(int nhealth) { maxHealth = nhealth; }
void player::setX(int nx) { x = nx; }
void player::setY(int ny) { y = ny; }
void player::setI(int ni) { i = ni; }
void player::setJ(int nj) { j = nj; }
void player::setWorldNumber(int x) { worldNumber = x; }
void player::setGold(int ngold) { gold = ngold; }
void player::up() { x--; }
void player::down() { x++; }
void player::left() { y--; }
void player::right() { y++; }
int player::getX() { return x; }
int player::getY() { return y; }
int player::getI() { return i; }
int player::getJ() { return j; }
int player::getWorldNumber() { return worldNumber; }
char player::getSymbol() { return symbol; }
std::string player::getName() { return name; }
int player::getHealth() { return health; }
int player::getLevel() { return level; }
int player::getExp() { return exp; }
int player::getAttack() { return attack; }
int player::getSpeed() { return speed; }
int player::getLuck() { return luck; }
int player::getDefense() { return defense;  }
int player::getMaxHealth() { return maxHealth; }
int player::getGold() { return gold; }
void player::setSymbol(char nsymbol) { symbol = nsymbol; }
void player::setName(std::string nname) { name = nname; }
void player::setLevel(int nlevel) { level = nlevel; }
void player::setExp(int nexp) { exp = nexp; }
void player::setAttack(int nattack) { attack = nattack; }
void player::setSpeed(int nspeed) { speed = nspeed; }
void player::setLuck(int nluck) { luck = nluck; }
void player::setDefense(int ndefense) { defense = ndefense; }