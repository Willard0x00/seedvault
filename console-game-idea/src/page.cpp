#include "page.h"
#include "player.h"

void page::loadStats()
{
	player player;

	system("CLS");
	std::cout << "---------------" << player.getName() << "---------------" << std::endl;
	std::cout << "Level: " << player.getLevel() << std::endl;
	std::cout << "Experience: " << player.getExp() << std::endl;
	std::cout << "Health: " << player.getHealth() << "/" << player.getMaxHealth() << std::endl;
	std::cout << "Attack: " << player.getAttack() << std::endl;
	std::cout << "Defense: " << player.getDefense() << std::endl;
	std::cout << "Speed: " << player.getSpeed() << std::endl;
	std::cout << "Luck: " << player.getLuck() << std::endl;
	std::cout << "Gold: " << player.getGold() << std::endl;
	system("PAUSE");

}