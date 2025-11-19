#include <iostream>
#include "player.h"

#ifndef MAP_H
#define MAP_H

class map
{
private:
public:
	static char world[17][41];
	static std::string worldName;
	static void initWorld1();
	static void initWorld2();
	static void initWorld3();
	static void initWorld4();
	static void initWorld5();
	static void initWorld6();
	static void initWorld7();
	static void initWorld8();
	static void initWorld9();
	static void initWorld10();
	static void initWorld11();
	static void initWorld12();
	static void initWorld13();
	static void initWorld14();
	static void initWorld15();
	static void initWorld16();
	static void initWorld17();
	static void initWorld18();
	static void initWorld19();
	static void initWorld20();
	static void initWorld21();
	static void initWorld22();
	static void initWorld23();
	static void initWorld24();
	static void initWorld25();
	static void initWorld26();
	static void initWorld27();
	static void initWorld28();
	static void initWorld29();
	static void initWorld30();
	static void initWorld31();
	static void initWorld32();
	static void initWorld33();
	static void initWorld34();
	static void initWorld35();
	static int enemyid;
	static int npcid;
	static int gateid;
	static int gateX;
	static int gateY;
	static int teleOne;
	static int teleTwo;
	static int teleThree;
	static int teleFour;
	static int xteleOne;
	static int yteleOne;
	static int xteleTwo;
	static int yteleTwo;
	static int xteleThree;
	static int yteleThree;
	static int xteleFour;
	static int yteleFour;
	static int iteleOne;
	static int iteleTwo;
	static int iteleThree;
	static int iteleFour;
	static int jteleOne;
	static int jteleTwo;
	static int jteleThree;
	static int jteleFour;
	static bool bteleOne;
	static bool bteleTwo;
	static bool bteleThree;
	static bool bteleFour;
	static bool dung1b1;
	static bool dung1b2;
	static bool dung1;
	static void createMapBounds(int x1, int y1, int x2, int y2);
	static void createEmptyMap();
	static void specialCheck(int x);
	static void gateOpen(int x);
	static void createHouseOne(int x, int y);
	static void createHouseTwo(int x, int y);
	static void createBushOne(int x, int y);
	static void createBushTwo(int x, int y);
	static void createTreeOne(int x, int y);
	static void createTreeTwo(int x, int y);
	static void createTreeThree(int x, int y);
	static void createTable(int x, int y);
	static void createPondOne(int x, int y);
	static void createPondTwo(int x, int y);
	static void createBridge(int x, int y);
	static void createRiver();
	static void createWell(int x, int y);
	static void createTent(int x, int y);
};

#endif