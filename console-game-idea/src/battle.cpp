#include "battle.h"

void loadEnemy(int id);
void loadFight(enemy& enemy);
void updateText(enemy& enemy);
void calcAttack(enemy& enemy);
void sendMessage(std::string s1, std::string s2);
void checkDeath(enemy& enemy);
void checkSpace(enemy& enemy, int x);
void lootDrop(enemy& enemy);
bool checkBoss(enemy& enemy);
int getInput();

bool fight = true;

void battle::battleEnemy(int nenemyid)
{
	loadEnemy(nenemyid);
}

void loadEnemy(int id)
{
	enemy enemy;

	switch (id)
	{
	case 1:
		enemy.setEnemy("Goblin", 3, 5, 15, 3, 1, 1, 0, 1, 1);
		break;
	case 2:
		enemy.setEnemy("Bandit", 6, 8, 45, 5, 2, 1, 2, 4, 2);
		break;
	case 3:
		enemy.setEnemy("Mage", 8, 10, 50, 7, 1, 1, 1, 7, 3);
		break;
	case 4:
		enemy.setEnemy("Zaimak", 15, 300, 300, 5, 5, 2, 4, 10, 4);
		break;
	}

	sendMessage("You encountered a ", enemy.getName());
	system("PAUSE");
	loadFight(enemy);
}

void loadFight(enemy& enemy)
{
	player player;

	int input = 0;

	fight = true;

	while (fight == true)
	{
		updateText(enemy);
		input = getInput();

		if (input == 1)
		{
			calcAttack(enemy);
		}
		else if (input == 3)
		{
			inventory::loadInventory();
		}
		else if (input == 4)
		{
			player.setX(player.getI());
			player.setY(player.getJ());
			fight = false;
		}
	}

	system("CLS");
}

void updateText(enemy& enemy)
{
	player player;

	system("CLS");
	std::cout << "--------------------" << enemy.getName() << "--------------------" << std::endl;
	checkSpace(enemy, enemy.getLevel());
	std::cout << "Level: " << enemy.getLevel() << enemy.getSpace() << "                    " << player.getName() << "'s Level: " << player.getLevel() << std::endl;
	checkSpace(enemy, enemy.getHealth());
	std::cout << "Health: " << enemy.getHealth() << enemy.getSpace() << "                   " << player.getName() << "'s Health: " << player.getHealth() << std::endl;
	checkSpace(enemy, enemy.getAttack());
	std::cout << "Attack: " << enemy.getAttack() << enemy.getSpace() << "                   " << player.getName() << "'s Attack: " << player.getAttack() << std::endl;
	checkSpace(enemy, enemy.getDefense());
	std::cout << "Defense: " << enemy.getDefense() << enemy.getSpace() << "                  " << player.getName() << "'s Defense: " << player.getDefense() << std::endl;
	checkSpace(enemy, enemy.getSpeed());
	std::cout << "Speed: " << enemy.getSpeed() << enemy.getSpace() << "                    " << player.getName() << "'s Speed: " << player.getSpeed() << std::endl;
	checkSpace(enemy, enemy.getLuck());
	std::cout << "Luck: " << enemy.getLuck() << enemy.getSpace() << "                     " << player.getName() << "'s Luck:  " << player.getLuck() << std::endl;
	checkSpace(enemy, enemy.getExp());
	std::cout << "Exp: " << enemy.getExp() << enemy.getSpace() << "                      " << player.getName() << "'s Exp: " << player.getExp() << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
	std::cout << "1. Attack" << std::endl;
	std::cout << "2. Use Item" << std::endl;
	std::cout << "3. Bag" << std::endl;
	std::cout << "4. Run" << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
}

void calcAttack(enemy& enemy)
{
	player player;

	int pdamage = 0;
	int edamage = 0;

	pdamage = player.getAttack();
	pdamage = pdamage + rand() % player.getLuck();
	pdamage = pdamage - enemy.getDefense();

	if (pdamage < 1)
	{
		pdamage = 0;
	}

	edamage = enemy.getAttack();
	edamage = edamage + rand() % enemy.getLuck();
	edamage = edamage - player.getDefense();

	if (edamage < 1)
	{
		edamage = 0;
	}

	if (player.getSpeed() >= enemy.getSpeed())
	{
		std::cout << player.getName() << " deals " << pdamage << " damage" << std::endl;
		enemy.setHealth((enemy.getHealth() - pdamage));
		checkDeath(enemy);
		if (fight == true)
		{
			std::cout << enemy.getName() << " deals " << edamage << " damage" << std::endl;
			player.setHealth((player.getHealth() - edamage));
			checkDeath(enemy);
		}
		system("PAUSE");
	}
	else if (player.getSpeed() < enemy.getSpeed())
	{
		std::cout << enemy.getName() << " deals " << edamage << " damage" << std::endl;
		player.setHealth((player.getHealth() - edamage));
		checkDeath(enemy);
		if (fight == true)
		{
			std::cout << player.getName() << " deals " << pdamage << " damage" << std::endl;
			enemy.setHealth((enemy.getHealth() - pdamage));
			checkDeath(enemy);
		}
		system("PAUSE");
	}
}

int getInput()
{
	int choice = 0;

	char key = ' ';

	key = _getch();

	switch (key)
	{
	case '1':
		choice = 1;
		break;
	case '2':
		choice = 2;
		break;
	case '3':
		choice = 3;
		break;
	case '4':
		choice = 4;
		break;
	default:
		getInput();
	}

	return choice;
}

void sendMessage(std::string s1, std::string s2)
{
	std::cout << s1;
	std::cout << s2 << std::endl;
}

void checkDeath(enemy& enemy)
{
	player player;

	if (player.getHealth() < 1)
	{
		std::cout << "YOU DIED" << std::endl;
		system("PAUSE");
		player.revive();
		player.setExp(0);
		player.setX(7);
		player.setY(7);
		map::initWorld1();
		fight = false;
	}
	else if (enemy.getHealth() < 1)
	{
		int exp;
		bool boss;
		exp = enemy.getExp();
		std::cout << "You killed " << enemy.getName() << std::endl;
		std::cout << "You gained " << enemy.getExp() << " Experience" << std::endl;
		system("PAUSE");
		player.addExp(exp);
		boss = checkBoss(enemy);
		if (boss == false)
		{
			npc::addKill(enemy.getid());
			lootDrop(enemy);
		}
		else if (boss == true)
		{
			npc::addKill(enemy.getid());
			inventory::addItem(enemy.getItem());
		}
		fight = false;

	}
}

void checkSpace(enemy& enemy, int x)
{
	if (x > 99)
	{
		enemy.setSpace("");
	}
	else if ((x > 9) & (x < 100))
	{
		enemy.setSpace(" ");
	}
	else
	{
		enemy.setSpace("  ");
	}
}

bool checkBoss(enemy& enemy)
{
	if (enemy.getid() == 4)
	{
		map::dung1 = true;
		map::dung1b1 = true;
		map::dung1b2 = true;
		return true;
	}
	else
	{
		return false;
	}
}

void lootDrop(enemy& enemy)
{
	int x = 0;
	x = rand() % + 4;
	std::cout << x << std::endl;
	if (x == 1)
	{
		x = rand() % 3;
		std::cout << x << std::endl;
		switch (x)
		{
		case 0:
			inventory::addItem(enemy.getItem());
			break;
		case 1:
			inventory::addItem(enemy.getItem() + 1);
			break;
		case 2:
			inventory::addItem(enemy.getItem() + 2);
			break;
		}
	}
}