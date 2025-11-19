#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include "map.h"
#include "player.h"
#include "battle.h"
#include "item.h"
#include "page.h"
#include "npc.h"

#pragma execution_character_set( "utf-8" )

void test();
void updateMap();
void playerMove();
void playerCheck();
void gameRun();
void loadWorld(int w);
void saveGame();
void loadGame();
char map::world[17][41];
std::string map::worldName;
int map::enemyid;
int map::npcid;
int map::gateid;
int map::gateX;
int map::gateY;
int map::teleOne;
int map::teleTwo;
int map::teleThree;
int map::teleFour;
int map::xteleOne;
int map::xteleTwo;
int map::xteleThree;
int map::xteleFour;
int map::yteleOne;
int map::yteleTwo;
int map::yteleThree;
int map::yteleFour;
int map::iteleOne;
int map::iteleTwo;
int map::iteleThree;
int map::iteleFour;
int map::jteleOne;
int map::jteleTwo;
int map::jteleThree;
int map::jteleFour;
bool map::bteleOne;
bool map::bteleTwo;
bool map::bteleThree;
bool map::bteleFour;
bool map::dung1b1;
bool map::dung1b2;
bool map::dung1;
int player::x;
int player::y;
int player::i;
int player::j;
int player::worldNumber;
char player::symbol;
std::string player::name;
int player::health;
int player::level;
int player::exp;
int player::attack;
int player::speed;
int player::luck;
int player::defense;
int player::maxHealth;
int player::gold;
int inventory::bag[20];

int main()
{
test();
system("PAUSE");
}

void test()
{
	system("chcp 65001");
	srand((unsigned int)time(NULL));
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1000, 600, TRUE);

	player player;
	player.setPlayer(7, 7, 'o', "Аё", 50, 1, 0, 2, 1, 1, 2, 50, 0);
	player.setWorldNumber(1);

	loadGame();

	loadWorld(player.getWorldNumber());
	gameRun();
}

void gameRun()
{
	bool exitGame = false;

	while (exitGame == false)
	{
			system("CLS");
			playerCheck();
			updateMap();
			playerMove();
	}
}

void updateMap()
{
	player player;
	int x;
	int y;

	map::world[player.getX()][player.getY()] = player.getSymbol();

	for (x = 0; x < 17; x++)
	{
		for (y = 0; y < 41; y++)
		{
			std::cout << map::world[x][y];
		}
		std::cout << std::endl;
	}
	std::cout << map::worldName << std::endl;
	std::cout << player.getX() << " ";
	std::cout << player.getY() << " " << player.getWorldNumber();
}

void playerMove()
{
	player player;
	char key = ' ';

	key = _getch();

		switch (key)
		{
		case 'w':
			map::world[player.getX()][player.getY()] = ' ';
			player.setI(player.getX());
			player.setJ(player.getY());
			player.up();
			break;
		case 's':
			map::world[player.getX()][player.getY()] = ' ';
			player.setI(player.getX());
			player.setJ(player.getY());
			player.down();
			break;
		case 'd':
			map::world[player.getX()][player.getY()] = ' ';
			player.setI(player.getX());
			player.setJ(player.getY());
			player.right();
			break;
		case 'a':
			map::world[player.getX()][player.getY()] = ' ';
			player.setI(player.getX());
			player.setJ(player.getY());
			player.left();
			break;
		case 'q':
			inventory::loadInventory();
			break;
		case 'e':
			page::loadStats();
			break;
		case 'z':
			saveGame();
			break;
		default:
			break;
		}
}

void playerCheck()
{
	player player;

	if (map::world[player.getX()][player.getY()] == ' ')
	{

	}
	else if ((map::world[player.getX()][player.getY()] == '#') || (map::world[player.getX()][player.getY()] == '|') || (map::world[player.getX()][player.getY()] == 'X') || (map::world[player.getX()][player.getY()] == '_') || (map::world[player.getX()][player.getY()] == '\\') || (map::world[player.getX()][player.getY()] == '/') || (map::world[player.getX()][player.getY()] == '[') || (map::world[player.getX()][player.getY()] == ']') || (map::world[player.getX()][player.getY()] == '+') || (map::world[player.getX()][player.getY()] == '-') || (map::world[player.getX()][player.getY()] == '0') || (map::world[player.getX()][player.getY()] == '`') || (map::world[player.getX()][player.getY()] == '+') || (map::world[player.getX()][player.getY()] == '^') || (map::world[player.getX()][player.getY()] == '='))
	{
		player.setX(player.getI());
		player.setY(player.getJ());
	}
	else if (map::world[player.getX()][player.getY()] == '&')
	{
		battle::battleEnemy(map::enemyid);
	}
	else if (map::world[player.getX()][player.getY()] == 'O')
	{
		player.setX(player.getI());
		player.setY(player.getJ());
		npc::interactNPC(map::npcid);
	}
	else if (map::world[player.getX()][player.getY()] == '.')
	{
		map::gateOpen(map::gateid);
	}
	else if (map::world[player.getX()][player.getY()] == '*')
	{
		map::specialCheck(player.getWorldNumber());
	}
	else if (map::world[player.getX()][player.getY()] == 'H')
	{
		player.setHealth(player.getMaxHealth());
		std::cout << "You Health has been restored" << std::endl;
	}
	else if (map::world[player.getX()][player.getY()] == '@')
	{
		if ((map::bteleOne == true) & (player.getX() == map::xteleOne) & (player.getY() == map::yteleOne))
		{
			player.setWorldNumber(map::teleOne);
			player.setX(map::iteleOne);
			player.setY(map::jteleOne);
			loadWorld(player.getWorldNumber());
		}
		else if ((map::bteleTwo == true) & (player.getX() == map::xteleTwo) & (player.getY() == map::yteleTwo))
		{
			player.setWorldNumber(map::teleTwo);
			player.setX(map::iteleTwo);
			player.setY(map::jteleTwo);
			loadWorld(player.getWorldNumber());
		}
		else if ((map::bteleThree == true) & (player.getX() == map::xteleThree) & (player.getY() == map::yteleThree))
		{
			player.setWorldNumber(map::teleThree);
			player.setX(map::iteleThree);
			player.setY(map::jteleThree);
			loadWorld(player.getWorldNumber());
		}
		else if ((map::bteleFour == true) & (player.getX() == map::xteleFour) & (player.getY() == map::yteleFour))
		{
			player.setWorldNumber(map::teleFour);
			player.setX(map::iteleFour);
			player.setY(map::jteleFour);
			loadWorld(player.getWorldNumber());
		}
	}
	else
	{
		//more conditions for collisions
	}
}

void loadWorld(int w)
{
	switch (w)
	{
	case 1: 
		map::initWorld1();
		break;
	case 2:
		map::initWorld2();
		break;
	case 3:
		map::initWorld3();
		break;
	case 4:
		map::initWorld4();
		break;
	case 5:
		map::initWorld5();
		break;
	case 6:
		map::initWorld6();
		break;
	case 7:
		map::initWorld7();
		break;
	case 8:
		map::initWorld8();
		break;
	case 9:
		map::initWorld9();
		break;
	case 10:
		map::initWorld10();
		break;
	case 11:
		map::initWorld11();
		break;
	case 12:
		map::initWorld12();
		break;
	case 13:
		map::initWorld13();
		break;
	case 14:
		map::initWorld14();
		break;
	case 15:
		map::initWorld15();
		break;
	case 16:
		map::initWorld16();
		break;
	case 17:
		map::initWorld17();
		break;
	case 18:
		map::initWorld18();
		break;
	case 19:
		map::initWorld19();
		break;
	case 20:
		map::initWorld20();
		break;
	case 21:
		map::initWorld21();
		break;
	case 22:
		map::initWorld22();
		break;
	case 23:
		map::initWorld23();
		break;
	case 24:
		map::initWorld24();
		break;
	case 25:
		map::initWorld25();
		break;
	case 26:
		map::initWorld26();
		break;
	case 27:
		map::initWorld27();
		break;
	case 28:
		map::initWorld28();
		break;
	case 29:
		map::initWorld29();
		break;
	case 30:
		map::initWorld30();
		break;
	case 31:
		map::initWorld31();
		break;
	case 32:
		map::initWorld32();
		break;
	case 33:
		map::initWorld33();
		break;
	case 34:
		map::initWorld34();
		break;
	case 35:
		map::initWorld35();
		break;

	}

	gameRun();
}

void saveGame()
{
	player player;
	std::ofstream savefile;

	savefile.open("save.txt");

	inventory::save(false);

	savefile << player.getX() << " " << player.getY() << " " << player.getI() << " " << player.getJ() << " " << player.getWorldNumber() << " " << player.getSymbol() << " " << player.getName() << " " << player.getHealth() << " " << player.getMaxHealth() << " " << player.getLevel() << " " << player.getExp() << " " << player.getAttack() << " " << player.getDefense() << " " << player.getSpeed() << " " << player.getLuck() << " " << player.getGold();

	inventory::save(true);

	savefile.close();
	savefile.open("dungeon.txt");
	savefile << map::dung1 << " " << map::dung1b1 << " " << map::dung1b2;
	savefile.close();

	npc::save();

	std::cout << "Game Saved" << std::endl;
	system("PAUSE");
}

void loadGame()
{
	player player;
	std::ifstream loadfile;

	std::string name;
	int x;
	int y;
	int i;
	int j;
	int worldnumber;
	char symbol;
	int health;
	int maxhealth;
	int level;
	int exp;
	int attack;
	int defense;
	int speed;
	int luck;
	int gold;

	loadfile.open("save.txt");
	loadfile >> x >> y >> i >> j >> worldnumber >> symbol >> name >> health >> maxhealth >> level >> exp >> attack >> defense >> speed >> luck >> gold;
	loadfile.close();

	std::cout << x << " " << y << " " << i << " " << j << " " << worldnumber << " " << symbol << " " << health << " " << maxhealth << " " << level << " " << exp << " " << attack << " " << defense << " " << speed << " " << luck << " " << gold << std::endl;

	player.setPlayer(x, y, symbol, name, health, level, exp, attack, speed, luck, defense, maxhealth, gold);
	player.setI(i);
	player.setJ(j);
	player.setWorldNumber(worldnumber);

	loadfile.open("dungeon.txt");
	loadfile >> map::dung1 >> map::dung1b1 >> map::dung1b2;
	loadfile.close();

	npc::load();
	inventory::load();

}