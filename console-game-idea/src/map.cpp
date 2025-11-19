#include "map.h"

bool checkDungeon();


void map::initWorld1()
{

	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Your Home";
	createMapBounds(x, y, xu, yu);

	//enviroment
	createHouseOne(2, 5);
	createBushTwo(6, 35);
	createBushTwo(6, 30);
	createBushTwo(9, 35);
	createBushTwo(9, 30);
	createTreeTwo(2, 16);

	//Enemys
	

	//x Enemy id
	enemyid = 0;
	npcid = 0;
	gateid = 0;
	gateX = 0;
	gateY = 0;

	//Tele
	world[8][40] = '@';
	bteleOne = true;
	xteleOne = 8;
	yteleOne = 40;
	iteleOne = 8;
	jteleOne = 1;
	teleOne = 2;

	bteleTwo = false;
	bteleThree = false;
	bteleFour = false;

}

void map::initWorld2()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Old Man";
	createMapBounds(x, y, xu, yu);
	createTreeThree(4, 18);

	world[10][18] = 'O';
	npcid = 0;

	world[8][0] = '@';
	bteleOne = true;
	xteleOne = 8;
	yteleOne = 0;
	iteleOne = 8;
	jteleOne = 39;
	teleOne = 1;

	world[8][40] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 40;
	iteleTwo = 8;
	jteleTwo = 1;
	teleTwo = 3;

	bteleThree = false;
	bteleFour = false;
}

void map::initWorld3()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Forest";
	createMapBounds(x, y, xu, yu);
	createTreeOne(2, 3);
	createTreeTwo(4, 13);
	createTreeOne(2, 23);
	createTreeTwo(6, 33);
	createTreeTwo(8, 4);
	createTreeOne(10, 25);
	
	world[10][12] = '&';
	world[13][35] = '&';
	enemyid = 1;

	world[8][0] = '@';
	bteleOne = true;
	xteleOne = 8;
	yteleOne = 0;
	iteleOne = 8;
	jteleOne = 39;
	teleOne = 2;

	world[16][20] = '@';
	bteleTwo = true;
	xteleTwo = 16;
	yteleTwo = 20;
	iteleTwo = 1;
	jteleTwo = 20;
	teleTwo = 4;

	world[0][20] = '@';
	bteleThree = true;
	xteleThree = 0;
	yteleThree = 20;
	iteleThree = 15;
	jteleThree = 20;
	teleThree = 6;

	world[8][40] = '@';
	bteleFour = true;
	xteleFour = 8;
	yteleFour = 40;
	iteleFour = 8;
	jteleFour = 1;
	teleFour = 8;
}

void map::initWorld4()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "South of Forest";
	createMapBounds(x, y, xu, yu);
	createHouseTwo(5, 30);
	createPondOne(10, 2);

	bteleOne = true;
	xteleOne = 9;
	yteleOne = 32;
	iteleOne = 10;
	jteleOne = 10;
	teleOne = 5;
	
	world[0][20] = '@';
	bteleTwo = true;
	xteleTwo = 0;
	yteleTwo = 20;
	iteleTwo = 15;
	jteleTwo = 20;
	teleTwo = 3;

	bteleThree = false;
	bteleFour = false;
}

void map::initWorld5()
{
	int x = 0;
	int y = 0;
	int xu = 12;
	int yu = 21;
	worldName = "Leon's House";
	createEmptyMap();
	createMapBounds(x, y, xu, yu);
	createTable(3, 3);

	world[7][7] = 'O';
	npcid = 1;

	world[11][10] = '@';
	bteleOne = true;
	xteleOne = 11;
	yteleOne = 10;
	iteleOne = 10;
	jteleOne = 32;
	teleOne = 4;

	bteleTwo = false;
	bteleThree = false;
	bteleFour = false;
}

void map::initWorld6()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Forest";
	createMapBounds(x, y, xu, yu);
	createTreeTwo(2, 2);
	createTreeTwo(10, 3);
	createTreeOne(3, 14);
	createTreeTwo(9, 18);
	createTreeOne(10, 32);
	createTreeTwo(1, 28);


	world[6][25] = '&';
	world[14][28] = '&';
	world[7][5] = '&';
	enemyid = 1;

	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 3;

	world[8][40] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 40;
	iteleTwo = 8;
	jteleTwo = 1;
	teleTwo = 7;

	bteleThree = false;
	bteleFour = false;
	
}

void map::initWorld7()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Forest";
	createMapBounds(x, y, xu, yu);
	createTreeOne(1, 4);
	createTreeOne(9, 6);
	createTreeTwo(2, 17);
	createTreeOne(7, 13);
	createTreeOne(8, 30);
	createTreeTwo(3, 33);
	createTreeOne(9, 22);

	world[13][31] = '&';
	world[5][26] = '&';
	world[4][12] = '&';
	enemyid = 1;

	world[8][0] = '@';
	bteleOne = true;
	xteleOne = 8;
	yteleOne = 0;
	iteleOne = 8;
	jteleOne = 39;
	teleOne = 6;

	world[16][20] = '@';
	bteleTwo = true;
	xteleTwo = 16;
	yteleTwo = 20;
	iteleTwo = 1;
	jteleTwo = 20;
	teleTwo = 8;

	world[0][20] = '@';
	bteleThree = true;
	xteleThree = 0;
	yteleThree = 20;
	iteleThree = 15;
	jteleThree = 20;
	teleThree = 9;

	bteleFour = false;

}

void map::initWorld8()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Forest";
	createMapBounds(x, y, xu, yu);
	createTreeOne(1, 3);
	createTreeTwo(9, 3);
	createTreeOne(3, 12);
	createTreeOne(6, 18);
	createTreeTwo(9, 26);
	createTreeTwo(2, 32);
	createTreeOne(10, 34);

	world[4][25] = '&';
	world[8][34] = '&';
	world[12][11] = '&';
	enemyid = 1;


	world[0][20] = '@';
	bteleOne = true;
	xteleOne = 0;
	yteleOne = 20;
	iteleOne = 15;
	jteleOne = 20;
	teleOne = 7;

	world[8][0] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 0;
	iteleTwo = 8;
	jteleTwo = 39;
	teleTwo = 3;

	bteleThree = false;
	bteleFour = false;
}

void map::initWorld9()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "River Crossing";
	createMapBounds(x, y, xu, yu);
	createRiver();
	createBridge(5, 30);


	world[8][31] = '+';
	world[8][33] = '+';

	world[8][32] = 'O';
	npcid = 2;



	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 7;

	world[0][20] = '@';
	bteleTwo = true;
	xteleTwo = 0;
	yteleTwo = 20;
	iteleTwo = 15;
	jteleTwo = 20;
	teleTwo = 10;

	bteleThree = false;
	bteleFour = false;
}

void map::initWorld10()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "East of Rooster Town";
	createMapBounds(x, y, xu, yu);
	createHouseOne(5, 6);
	createHouseOne(8, 30);
	createTreeOne(3, 27);

	world[13][32] = 'O';
	npcid = 5;

	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 9;

	world[8][0] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 0;
	iteleTwo = 8;
	jteleTwo = 39;
	teleTwo = 11;

	bteleThree = false;
	bteleFour = false;

}

void map::initWorld11()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Rooster Town";
	createMapBounds(x, y, xu, yu);
	for (y = 1; y < 39; y++)
	{
		world[10][y] = '_';
	}
	for (y = 1; y < 39; y++)
	{
		world[6][y] = '_';
	}
	createHouseOne(2, 3);
	createHouseOne(2, 11);
	createHouseOne(2, 23);
	createHouseOne(2, 31);
	createHouseTwo(9, 7);
	createHouseOne(9, 27);

	world[1][18] = '+';
	world[1][22] = '+';
	world[6][22] = '+';
	world[6][21] = ' ';
	world[6][20] = ' ';
	world[6][19] = ' ';
	world[6][18] = '+';
	world[10][18] = '+';
	world[10][19] = ' ';
	world[10][20] = ' ';
	world[10][21] = ' ';
	world[10][22] = '+';

	
	for (x = 2; x < 6; x++)
	{
		world[x][18] = '|';
	}
	for (x = 2; x < 6; x++)
	{
		world[x][22] = '|';
	}
	for (x = 11; x < 14; x++)
	{
		world[x][18] = '|';
	}
	for (x = 11; x < 14; x++)
	{
		world[x][22] = '|';
	}

	world[0][20] = '@';
	bteleOne = true;
	xteleOne = 0;
	yteleOne = 20;
	iteleOne = 15;
	jteleOne = 20;
	teleOne = 12;

	world[8][40] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 40;
	iteleTwo = 8;
	jteleTwo = 1;
	teleTwo  = 10;

	world[13][9] = '@';
	bteleThree = true;
	xteleThree = 13;
	yteleThree = 9;
	iteleThree = 10;
	jteleThree = 10;
	teleThree = 13;

	world[8][0] = '@';
	bteleFour = true;
	xteleFour = 8;
	yteleFour = 0;
	iteleFour = 8;
	jteleFour = 39;
	teleFour = 25;
}

void map::initWorld12()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Rooster Town";
	createMapBounds(x, y, xu, yu);
	createWell(6, 16);
	createHouseOne(1, 4);
	createHouseOne(9, 4);
	createHouseOne(1, 30);
	createHouseOne(9, 30);

	world[15][24] = '+';
	world[13][24] = '|';
	world[12][24] = '/';
	world[11][25] = '/';
	world[10][26] = '/';
	world[9][27] = '|';
	world[8][27] = ' ';
	world[7][27] = '|';
	world[6][26] = '\\';
	world[5][25] = '\\';
	world[4][24] = '\\';
	world[3][24] = '|';
	world[2][24] = '|';
	world[1][24] = '+';

	world[15][16] = '+';
	world[13][16] = '|';
	world[12][16] = '\\';
	world[11][15] = '\\';
	world[10][14] = '\\';
	world[9][13] = '|';
	world[8][13] = ' ';
	world[7][13] = '|';
	world[6][14] = '/';
	world[5][15] = '/';
	world[4][16] = '/';
	world[3][16] = '|';
	world[2][16] = '|';
	world[1][16] = '+';

	world[14][36] = '|';
	world[15][36] = '+';
	world[15][25] = '_';
	world[15][26] = '_';
	world[15][27] = '_';
	world[15][28] = '_';
	world[15][29] = '_';
	world[15][30] = '_';
	world[15][31] = '_';
	world[15][32] = '_';
	world[15][33] = '_';
	world[15][34] = '_';
	world[15][35] = '_';
	world[13][25] = '_';
	world[13][26] = '_';
	world[13][27] = '_';
	world[13][28] = '_';
	world[13][29] = '_';
	world[13][15] = '_';
	world[13][14] = '_';
	world[13][13] = '_';
	world[13][12] = '_';
	world[13][11] = '_';

	world[14][4] = '|';
	world[15][4] = '+';
	world[15][5] = '_';
	world[15][6] = '_';
	world[15][7] = '_';
	world[15][8] = '_';
	world[15][9] = '_';
	world[15][10] = '_';
	world[15][11] = '_';
	world[15][12] = '_';
	world[15][13] = '_';
	world[15][14] = '_';
	world[15][15] = '_';

	world[6][36] = '|';
	world[7][36] = '|';
	world[8][36] = '|';
	world[9][36] = '+';
	world[9][35] = '_';
	world[9][28] = '_';
	world[9][29] = '_';
	world[9][30] = '_';
	world[9][31] = '_';

	world[7][29] = '+';
	world[6][29] = '|';
	world[5][29] = '+';
	world[7][28] = '_';

	world[9][12] = '_';
	world[9][11] = '_';
	world[9][10] = '_';
	world[9][9] = '_';
	world[9][4] = '+';
	world[9][5] = '_';
	world[8][4] = '|';
	world[7][4] = '|';
	world[6][4] = '|';
	world[5][11] = '+';
	world[6][11] = '|';
	world[7][11] = '+';
	world[7][12] = '_';

	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 11;

	world[0][20] = '@';
	bteleTwo = true;
	xteleTwo = 0;
	yteleTwo = 20;
	iteleTwo = 15;
	jteleTwo = 20;
	teleTwo = 14;

	bteleThree = false;
	bteleFour = false;
}

void map::initWorld13()
{
	int x = 0;
	int y = 0;
	int xu = 12;
	int yu = 21;
	worldName = "Lilo's House";
	createEmptyMap();
	createMapBounds(x, y, xu, yu);
	createTable(3, 8);

	world[7][7] = 'O';
	npcid = 4;

	world[11][10] = '@';
	bteleOne = true;
	xteleOne = 11;
	yteleOne = 10;
	iteleOne = 14;
	jteleOne = 9;
	teleOne = 11;

	bteleTwo = false;
	bteleThree = false;
	bteleFour = false;
}

void map::initWorld14()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Rooster Town";
	createMapBounds(x, y, xu, yu);
	for (y = 1; y < 39; y++)
	{
		world[10][y] = '_';
	}
	for (y = 1; y < 39; y++)
	{
		world[6][y] = '_';
	}
	createHouseOne(2, 3);
	createHouseTwo(2, 11);
	createHouseOne(2, 23);
	createHouseOne(2, 31);
	createHouseOne(9, 7);
	createHouseOne(9, 27);

	world[1][18] = '+';
	world[1][22] = '+';
	world[6][22] = '+';
	world[6][21] = ' ';
	world[6][20] = ' ';
	world[6][19] = ' ';
	world[6][18] = '+';
	world[10][18] = '+';
	world[10][19] = ' ';
	world[10][20] = ' ';
	world[10][21] = ' ';
	world[10][22] = '+';


	for (x = 2; x < 6; x++)
	{
		world[x][18] = '|';
	}
	for (x = 2; x < 6; x++)
	{
		world[x][22] = '|';
	}
	for (x = 11; x < 14; x++)
	{
		world[x][18] = '|';
	}
	for (x = 11; x < 14; x++)
	{
		world[x][22] = '|';
	}
	
	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 12;

	world[0][20] = '@';
	bteleTwo = true;
	xteleTwo = 0;
	yteleTwo = 20;
	iteleTwo = 15;
	jteleTwo = 20;
	teleTwo = 15;

	world[6][13] = '@';
	bteleThree = true;
	xteleThree = 6;
	yteleThree = 13;
	iteleThree = 10;
	jteleThree = 10;
	teleThree = 17;

	bteleFour = false;

}

void map::initWorld15()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "North of Rooster Town";
	createMapBounds(x, y, xu, yu);
	createTreeOne(2, 3);
	createTreeOne(8, 3);
	createTreeOne(2, 33);
	createTreeOne(8, 33);
	createBushTwo(1, 13);
	createBushTwo(1, 25);
	createBushTwo(4, 13);
	createBushTwo(4, 25);
	createBushTwo(7, 13);
	createBushTwo(7, 25);
	createBushTwo(10, 13);
	createBushTwo(10, 25);
	createBushTwo(13, 13);
	createBushTwo(13, 25);
	world[1][18] = '+';
	world[1][22] = '+';
	world[15][18] = '+';
	world[15][22] = '+';
	for (x = 2; x < 15; x++)
	{
		world[x][18] = '|';
	}
	for (x = 2; x < 15; x++)
	{
		world[x][22] = '|';
	}
	
	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 14;

	world[0][20] = '@';
	bteleTwo = true;
	xteleTwo = 0;
	yteleTwo = 20;
	iteleTwo = 15;
	jteleTwo = 20;
	teleTwo = 16;

	teleThree = false;
	teleFour = false;
}

void map::initWorld16()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Outskirts";
	createMapBounds(x, y, xu, yu);
	createBushTwo(5, 12);
	createBushTwo(9, 29);

	world[6][9] = '&';
	world[10][34] = '&';
	enemyid = 2;

	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 15;

	world[8][0] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 0;
	iteleTwo = 8;
	jteleTwo = 39;
	teleTwo = 18;

	world[0][20] = '@';
	bteleThree = true;
	xteleThree = 0;
	yteleThree = 20;
	iteleThree = 15;
	jteleThree = 20;
	teleThree = 19;

	teleFour = false;
}


void map::initWorld17()
{
	int x = 0;
	int y = 0;
	int xu = 12;
	int yu = 21;
	worldName = "Gary's House";
	createEmptyMap();
	createMapBounds(x, y, xu, yu);
	createTable(2, 5);

	world[7][7] = 'O';
	npcid = 3;

	world[11][10] = '@';
	bteleOne = true;
	xteleOne = 11;
	yteleOne = 10;
	iteleOne = 7;
	jteleOne = 13;
	teleOne = 14;

	bteleTwo = false;
	bteleThree = false;
	bteleFour = false;
}

void map::initWorld18()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Outskirts";
	createMapBounds(x, y, xu, yu);
	createBushTwo(2, 10);
	createBushTwo(7, 25);
	createBushTwo(11, 30);
	createBushTwo(8, 8);

	world[3][7] = '&';
	world[8][22] = '&';
	world[12][35] = '&';
	world[9][5] = '&';
	enemyid = 2;

	world[0][20] = '@';
	bteleOne = true;
	xteleOne = 0;
	yteleOne = 20;
	iteleOne = 15;
	jteleOne = 20;
	teleOne = 20;

	world[8][40] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 40;
	iteleTwo = 8;
	jteleTwo = 1;
	teleTwo = 16;

	teleThree = false;
	teleFour = false;
}
void map::initWorld19()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Outskirts";
	createMapBounds(x, y, xu, yu);
	createBushTwo(1, 10);
	createBushTwo(3, 25);
	createBushTwo(11, 6);
	createBushTwo(13, 30);

	world[12][3] = '&';
	world[2][7] = '&';
	world[4][30] = '&';
	world[14][35] = '&';
	enemyid = 2;

	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 16;

	world[8][0] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 0;
	iteleTwo = 8;
	jteleTwo = 39;
	teleTwo = 20;

	teleThree = false;
	teleFour = false;
}
void map::initWorld20()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "Outskirts";
	createMapBounds(x, y, xu, yu);
	createTent(2, 7);
	createBushTwo(10, 4);
	createBushTwo(13, 30);

	world[6][23] = 'O';
	npcid = 6;

	world[16][20] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 20;
	iteleOne = 1;
	jteleOne = 20;
	teleOne = 18;

	world[8][40] = '@';
	bteleTwo = true;
	xteleTwo = 8;
	yteleTwo = 40;
	iteleTwo = 8;
	jteleTwo = 1;
	teleTwo = 19;

	world[6][19] = '@';
	bteleThree = true;
	xteleThree = 6;
	yteleThree = 19;
	iteleThree = 15;
	jteleThree = 15;
	teleThree = 21;

	teleFour = false;
}
void map::initWorld21()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 31;
	worldName = "Magical Tent";
	createEmptyMap();
	createMapBounds(x, y, xu, yu);

	for (x = 1; x < 16; x++)
	{
		world[x][13] = '|';
	}
	for (x = 1; x < 16; x++)
	{
		world[x][17] = '|';
	}

	for (y = 1; y < 13; y++)
	{
		world[6][y] = '_';
	}

	for (x = 1; x < 16; x++)
	{
		for (y = 18; y < 30; y++)
		{
			world[x][y] = '#';
		}
	}

	world[8][11] = '*';

	world[8][17] = 'X';
	world[3][13] = '&';
	enemyid = 3;

	if (dung1b1 == true)
	{
		world[8][17] = ' ';
		world[3][13] = ' ';
	}

	world[8][18] = ' ';
	world[8][19] = ' ';
	world[9][19] = ' ';
	world[10][19] = ' ';
	world[10][20] = ' ';
	world[10][21] = ' ';
	world[9][21] = ' ';
	world[8][21] = ' ';
	world[8][22] = ' ';
	world[8][23] = ' ';
	world[9][23] = ' ';
	world[10][23] = ' ';
	world[11][23] = ' ';
	world[12][23] = ' ';
	world[12][22] = ' ';
	world[12][21] = ' ';
	world[12][20] = ' ';
	world[13][20] = ' ';
	world[14][20] = ' ';
	world[14][19] = ' ';
	world[14][18] = ' ';
	world[13][18] = ' ';
	world[12][18] = ' ';
	world[14][21] = ' ';
	world[14][22] = ' ';
	world[15][22] = ' ';
	world[15][23] = ' ';
	world[15][24] = ' ';
	world[15][25] = ' ';
	world[15][26] = ' ';
	world[15][27] = ' ';
	world[14][27] = ' ';
	world[13][27] = ' ';
	world[13][26] = ' ';
	world[13][25] = ' ';
	world[14][28] = ' ';
	world[14][29] = ' ';
	world[13][29] = ' ';
	world[12][29] = ' ';
	world[7][19] = ' ';
	world[6][19] = ' ';
	world[5][19] = ' ';
	world[5][20] = ' ';
	world[4][20] = ' ';
	world[3][20] = ' ';
	world[3][19] = ' ';
	world[3][18] = ' ';
	world[2][18] = ' ';
	world[1][18] = ' ';
	world[1][19] = ' ';
	world[1][20] = ' ';
	world[1][21] = ' ';
	world[1][22] = ' ';
	world[1][23] = ' ';
	world[1][24] = ' ';
	world[1][25] = ' ';
	world[14][29] = ' ';
	world[13][29] = ' ';
	world[12][29] = ' ';
	world[11][29] = ' ';
	world[11][28] = ' ';
	world[11][27] = ' ';
	world[11][26] = ' ';
	world[11][25] = ' ';
	world[10][25] = ' ';
	world[9][25] = ' ';
	world[9][26] = ' ';
	world[9][27] = ' ';
	world[9][28] = ' ';
	world[8][28] = ' ';
	world[8][29] = ' ';
	world[7][28] = ' ';
	world[7][27] = ' ';
	world[7][20] = ' ';
	world[6][26] = ' ';
	world[6][25] = ' ';
	world[6][24] = ' ';
	world[6][23] = ' ';
	world[3][21] = ' ';
	world[3][22] = ' ';
	world[3][23] = ' ';
	world[4][23] = ' ';
	world[4][24] = ' ';
	world[4][25] = ' ';
	world[4][26] = ' ';
	world[3][26] = ' ';
	world[3][27] = ' ';
	world[3][28] = ' ';
	world[2][28] = ' ';
	world[1][28] = ' ';
	world[4][28] = ' ';
	world[5][28] = ' ';
	world[5][29] = ' ';
	world[6][29] = ' ';
	world[7][26] = ' ';

	world[3][28] = 'X';
	world[12][18] = '.';
	world[2][28] = '.';
	world[4][28] = '.';
	gateid = 1;
	gateX = 3;
	gateY = 28;

	world[6][23] = 'O';
	npcid = 7;

	world[16][15] = '@';
	bteleOne = true;
	xteleOne = 16;
	yteleOne = 15;
	iteleOne = 7;
	jteleOne = 19;
	teleOne = 20;

	world[3][2] = '@';
	bteleTwo = true;
	xteleTwo = 3;
	yteleTwo = 2;
	iteleTwo = 3;
	jteleTwo = 3;
	teleTwo = 22;

	world[1][29] = '@';
	bteleThree = true;
	xteleThree = 1;
	yteleThree = 29;
	iteleThree = 10;
	jteleThree = 5;
	teleThree = 22;

	world[6][29] = '@';
	bteleFour = true;
	xteleFour = 6;
	yteleFour = 29;
	iteleFour = 13;
	jteleFour = 22;
	teleFour = 23;
}
void map::initWorld22()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 31;
	worldName = "Magical Tent";
	createEmptyMap();
	createMapBounds(x, y, xu, yu);

	for (y = 1; y < 30; y++)
	{
		world[6][y] = '_';
	}

	for (y = 1; y < 30; y++)
	{
		world[5][y] = '#';
		world[1][y] = '#';
	}

	for (y = 6; y < 29; y++)
	{
		world[3][y] = '#';
	}

	if (dung1b1 == false)
	{
		world[3][29] = '.';
		world[4][25] = '&';
		enemyid = 3;
	}

	world[2][25] = '*';

	for (x = 7; x < 16; x++)
	{
		world[x][8] = '|';
		world[x][10] = '|';
		world[x][12] = '|';
		world[x][14] = '|';
		world[x][16] = '|';
		world[x][18] = '|';
		world[x][20] = '|';
		world[x][22] = '|';
		world[x][24] = '|';
		world[x][26] = '|';
	}

	world[8][8] = ' ';
	world[13][10] = ' ';
	world[15][12] = ' ';
	world[11][14] = ' ';
	world[9][16] = ' ';
	world[14][18] = ' ';
	world[7][20] = ' ';
	world[12][22] = ' ';
	world[10][24] = ' ';
	world[14][26] = ' ';

	if (dung1b2 == false)
	{
		world[8][8] = '&';
		world[13][10] = '&';
		world[15][12] = '&';
		world[11][14] = '&';
		world[9][16] = '&';
		world[14][18] = '&';
		world[7][20] = '&';
		world[12][22] = '&';
		world[10][24] = '&';
		world[14][26] = '&';
		enemyid = 3;
	}

	world[3][2] = '@';
	bteleOne = true;
	xteleOne = 3;
	yteleOne = 2;
	iteleOne = 3;
	jteleOne = 3;
	teleOne = 21;

	world[10][4] = '@';
	bteleTwo = true;
	xteleTwo = 10;
	yteleTwo = 4;
	iteleTwo = 1;
	jteleTwo = 28;
	teleTwo = 21;

	world[10][28] = '@';
	bteleThree = true;
	xteleThree = 10;
	yteleThree = 28;
	iteleThree = 13;
	jteleThree = 7;
	teleThree = 23;

	bteleFour = false;
}
void map::initWorld23()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 31;
	worldName = "Magical Tent";
	createEmptyMap();
	createMapBounds(x, y, xu, yu);

	for (x = 1; x < 16; x++)
	{
		world[x][14] = '|';
	}

	world[15][14] = ' ';

	for (y = 1; y < 14; y++)
	{
		world[11][y] = '-';
		world[8][y] = '-';
		world[5][y] = '-';
	}

	for (y = 15; y < 29; y++)
	{
		world[5][y] = '_';
	}

	world[5][22] = ' ';

	if (dung1b2 == false)
	{
		world[5][22] = 'X';
		gateid = 1;
		gateX = 5;
		gateY = 22;
	}

	world[11][7] = '*';
	world[11][10] = '*';
	world[11][4] = '*';
	world[8][7] = '*';
	world[8][10] = '*';
	world[8][4] = '*';
	world[5][7] = '*';
	world[5][10] = '*';
	world[5][4] = '*';

	if (dung1b2 == false)
	{
		world[1][7] = '.';
	}

	world[1][22] = '*';
	world[3][22] = 'H';

	world[14][7] = '@';
	bteleOne = true;
	xteleOne = 14;
	yteleOne = 7;
	iteleOne = 11;
	jteleOne = 28;
	teleOne = 22;

	world[14][22] = '@';
	bteleTwo = true;
	xteleTwo = 14;
	yteleTwo = 22;
	iteleTwo = 5;
	jteleTwo = 29;
	teleTwo = 21;


}
void map::initWorld24()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 31;
	worldName = "Magical Tent";
	createEmptyMap();
	createMapBounds(x, y, xu, yu);

	world[5][10] = '#';
	world[5][9] = '#';
	world[5][11] = '#';
	world[6][10] = '#';
	world[4][10] = '#';

	world[5][20] = '#';
	world[5][21] = '#';
	world[5][19] = '#';
	world[4][20] = '#';
	world[6][20] = '#';

	world[10][10] = '#';
	world[10][9] = '#';
	world[10][11] = '#';
	world[9][10] = '#';
	world[11][10] = '#';

	world[10][20] = '#';
	world[10][21] = '#';
	world[10][19] = '#';
	world[11][20] = '#';
	world[9][20] = '#';

	world[13][27] = '#';
	world[12][28] = '#';
	world[11][29] = '#';
	world[14][26] = '#';
	world[15][25] = '#';

	world[13][3] = '#';
	world[12][2] = '#';
	world[11][1] = '#';
	world[14][4] = '#';
	world[15][5] = '#';

	world[3][3] = '#';
	world[4][2] = '#';
	world[5][1] = '#';
	world[2][4] = '#';
	world[1][5] = '#';

	world[3][27] = '#';
	world[4][28] = '#';
	world[5][29] = '#';
	world[2][26] = '#';
	world[1][25] = '#';

	if (dung1 == false)
	{
		world[7][15] = '&';
		enemyid = 4;
	}

	world[1][15] = '*';
}
void map::initWorld25()
{
	int x = 0;
	int y = 0;
	int xu = 17;
	int yu = 41;
	worldName = "West of Rooster Town";
	createMapBounds(x, y, xu, yu);

	world[8][40] = '@';
	bteleOne = true;
	xteleOne = 8;
	yteleOne = 40;
	iteleOne = 8;
	jteleOne = 1;
	teleOne = 11;
}
void map::initWorld26()
{

}
void map::initWorld27()
{

}
void map::initWorld28()
{

}

void map::initWorld29()
{

}
void map::initWorld30()
{

}
void map::initWorld31()
{

}
void map::initWorld32()
{

}
void map::initWorld33()
{

}
void map::initWorld34()
{

}
void map::initWorld35()
{

}

void map::createMapBounds(int x1, int y1, int x2, int y2)
{
	int x;
	int y;

	y = y1;

	for (x = x1; x < x2; x++)
	{
		world[x][y] = '#';
	}

	y = y2 - 1;

	for (x = x1; x < x2; x++)
	{
		world[x][y] = '#';
	}

	x = x1;

	for (y = y1; y < y2; y++)
	{
		world[x][y] = '#';
	}

	x = x2 - 1;

	for (y = y1; y < y2; y++)
	{
		world[x][y] = '#';
	}

	for (x = x1 + 1; x < x2 - 1; x++)
	{
		for (y = y1 + 1; y < y2 - 1; y++)
		{
			world[x][y] = ' ';
		}
	}
}

void map::createEmptyMap()
{
	int x;
	int y;

	for (x = 0; x < 17; x++)
	{
		for (y = 0; y < 41; y++)
		{
			world[x][y] = ' ';
		}
	}

}



void map::gateOpen(int x)
{
	bool check = false;
	check = checkDungeon();
	
	if (check == false)
	{
		if (x == 1)
		{
			world[gateX][gateY] = ' ';
			gateid = 0;
		}
	}
}

bool checkDungeon()
{
	player player;

	if (player.getWorldNumber() == 22)
	{
		map::dung1b1 = true;
		return true;
	}
	else if (player.getWorldNumber() == 23)
	{
		map::dung1b2 = true;
		return false;
	}

	return false;
}

void map::specialCheck(int x)
{
	player player;

	if (x == 22)
	{
		player.setWorldNumber(21);
		player.setX(15);
		player.setY(15);
		map::initWorld21();
		std::cout << "You fell" << std::endl;
	}
	else if (x == 21)
	{
		player.setWorldNumber(24);
		player.setX(15);
		player.setY(15);
		map::initWorld24();
	}
	else if (x == 23)
	{
		if ((player.getX() == 11) & (player.getY() == 4))
		{
			player.setWorldNumber(21);
			player.setX(13);
			player.setY(25);
			map::initWorld21();
			std::cout << "You fell" << std::endl;
		}
		else if ((player.getX() == 11) & (player.getY() == 10))
		{
			player.setWorldNumber(21);
			player.setX(13);
			player.setY(25);
			map::initWorld21();
			std::cout << "You fell" << std::endl;
		}
		else if ((player.getX() == 8) & (player.getY() == 7))
		{
			player.setWorldNumber(21);
			player.setX(13);
			player.setY(25);
			map::initWorld21();
			std::cout << "You fell" << std::endl;
		}
		else if ((player.getX() == 8) & (player.getY() == 4))
		{
			player.setWorldNumber(21);
			player.setX(13);
			player.setY(25);
			map::initWorld21();
			std::cout << "You fell" << std::endl;
		}
		else if ((player.getX() == 5) & (player.getY() == 7))
		{
			player.setWorldNumber(21);
			player.setX(13);
			player.setY(25);
			map::initWorld21();
			std::cout << "You fell" << std::endl;
		}
		else if ((player.getX() == 5) & (player.getY() == 10))
		{
			player.setWorldNumber(21);
			player.setX(13);
			player.setY(25);
			map::initWorld21();
			std::cout << "You fell" << std::endl;
		}
		else if ((player.getX() == 1) & (player.getY() == 22))
		{
			player.setWorldNumber(21);
			player.setX(15);
			player.setY(5);
			map::initWorld21();
		}
	}
	else if (x == 24)
	{
		player.setWorldNumber(20);
		player.setX(7);
		player.setY(19);
		map::initWorld20();
	}
}

void map::createHouseOne(int x, int y)
{

	world[x + 2][y] = '/';
	world[x + 3][y] = '|';
	world[x + 4][y] = '|';
	world[x][y + 1] = ' ';
	world[x + 1][y + 1] = '/';
	world[x + 2][y + 1] = '_';
	world[x + 3][y + 1] = ' ';
	world[x + 4][y + 1] = '|';
	world[x][y + 2] = '_';
	world[x + 1][y + 2] = '_';
	world[x + 2][y + 2] = '_';
	world[x + 3][y + 2] = '_';
	world[x + 4][y + 2] = '#';
	world[x][y + 3] = '_';
	world[x + 1][y + 3] = '_';
	world[x + 2][y + 3] = '_';
	world[x + 3][y + 3] = ' ';
	world[x + 4][y + 3] = '|';
	world[x][y + 4] = '_';
	world[x + 1][y + 4] = '_';
	world[x + 2][y + 4] = '_';
	world[x + 3][y + 4] = '[';
	world[x + 4][y + 4] = '_';
	world[x + 1][y + 5] = '\\';
	world[x + 2][y + 5] = '_';
	world[x + 3][y + 5] = ']';
	world[x + 4][y + 5] = '_';
	world[x + 2][y + 6] = '\\';
	world[x + 3][y + 6] = '|';
	world[x + 4][y + 6] = '|';
}

void map::createHouseTwo(int x, int y)
{

	world[x + 2][y] = '/';
	world[x + 3][y] = '|';
	world[x + 4][y] = '|';
	world[x + 1][y + 1] = '/';
	world[x + 2][y + 1] = '_';
	world[x + 3][y + 1] = ' ';
	world[x + 4][y + 1] = '|';
	world[x][y + 2] = '_';
	world[x + 1][y + 2] = '_';
	world[x + 2][y + 2] = '_';
	world[x + 3][y + 2] = '_';
	world[x + 4][y + 2] = '@';
	world[x][y + 3] = '_';
	world[x + 1][y + 3] = '_';
	world[x + 2][y + 3] = '_';
	world[x + 3][y + 3] = ' ';
	world[x + 4][y + 3] = '|';
	world[x][y + 4] = '_';
	world[x + 1][y + 4] = '_';
	world[x + 2][y + 4] = '_';
	world[x + 3][y + 4] = '[';
	world[x + 4][y + 4] = '_';
	world[x + 1][y + 5] = '\\';
	world[x + 2][y + 5] = '_';
	world[x + 3][y + 5] = ']';
	world[x + 4][y + 5] = '_';
	world[x + 2][y + 6] = '\\';
	world[x + 3][y + 6] = '|';
	world[x + 4][y + 6] = '|';
}

void map::createBushOne(int x, int y)
{
	world[x][y] = '0';
	world[x + 1][y] = '0';
	world[x + 2][y] = '0';
	world[x][y + 1] = '0';
	world[x + 1][y + 1] = '0';
	world[x + 2][y + 1] = '0';
	world[x][y + 2] = '0';
	world[x + 1][y + 2] = '|';
	world[x + 2][y + 2] = '|';
	world[x][y + 3] = '0';
	world[x + 1][y + 3] = '0';
	world[x + 2][y + 3] = '0';
	world[x][y + 4] = '0';
	world[x + 1][y + 4] = '0';
	world[x + 2][y + 4] = '0';
}

void map::createBushTwo(int x, int y)
{
	world[x][y] = '0';
	world[x + 1][y] = '0';
	world[x][y + 1] = '0';
	world[x + 1][y + 1] = '|';
	world[x][y + 2] = '0';
	world[x + 1][y + 2] = '0';
}

void map::createTreeOne(int x, int y)
{
	world[x][y] = ' ';
	world[x + 1][y] = '0';
	world[x + 2][y] = '0';
	world[x + 3][y] = '0';
	world[x + 4][y] = ' ';
	world[x][y + 1] = '0';
	world[x + 1][y + 1] = '0';
	world[x + 2][y + 1] = '0';
	world[x + 3][y + 1] = ' ';
	world[x + 4][y + 1] = ' ';
	world[x][y + 2] = '0';
	world[x + 1][y + 2] = '0';
	world[x + 2][y + 2] = '|';
	world[x + 3][y + 2] = '|';
	world[x + 4][y + 2] = '|';
	world[x][y + 3] = '0';
	world[x + 1][y + 3] = '0';
	world[x + 2][y + 3] = '0';
	world[x + 3][y + 3] = ' ';
	world[x + 4][y + 3] = ' ';
	world[x][y + 4] = ' ';
	world[x + 1][y + 4] = '0';
	world[x + 2][y + 4] = '0';
	world[x + 3][y + 4] = '0';
	world[x + 4][y + 4] = ' ';
}

void map::createTreeTwo(int x, int y)
{
	world[x][y] = ' ';
	world[x + 1][y] = '0';
	world[x + 2][y] = '0';
	world[x + 3][y] = '0';
	world[x + 4][y] = ' ';
	world[x][y + 1] = '0';
	world[x + 1][y + 1] = '0';
	world[x + 2][y + 1] = '0';
	world[x + 3][y + 1] = '0';
	world[x + 4][y + 1] = ' ';
	world[x][y + 2] = '0';
	world[x + 1][y + 2] = '0';
	world[x + 2][y + 2] = '|';
	world[x + 3][y + 2] = '|';
	world[x + 4][y + 2] = '|';
	world[x][y + 3] = '0';
	world[x + 1][y + 3] = '0';
	world[x + 2][y + 3] = '0';
	world[x + 3][y + 3] = '0';
	world[x + 4][y + 3] = ' ';
	world[x][y + 4] = ' ';
	world[x + 1][y + 4] = '0';
	world[x + 2][y + 4] = '0';
	world[x + 3][y + 4] = '0';
	world[x + 4][y + 4] = ' ';
}

void map::createTreeThree(int x, int y)
{
	world[x][y] = ' ';
	world[x + 1][y] = '0';
	world[x + 2][y] = '0';
	world[x + 3][y] = '0';
	world[x + 4][y] = '0';
	world[x][y + 1] = '0';
	world[x + 1][y + 1] = '0';
	world[x + 2][y + 1] = '0';
	world[x + 3][y + 1] = '0';
	world[x + 4][y + 1] = ' ';
	world[x][y + 2] = '0';
	world[x + 1][y + 2] = '0';
	world[x + 2][y + 2] = '|';
	world[x + 3][y + 2] = '|';
	world[x + 4][y + 2] = '|';
	world[x + 5][y + 2] = '|';
	world[x][y + 3] = '0';
	world[x + 1][y + 3] = '0';
	world[x + 2][y + 3] = '0';
	world[x + 3][y + 3] = '0';
	world[x + 4][y + 3] = ' ';
	world[x][y + 4] = ' ';
	world[x + 1][y + 4] = '0';
	world[x + 2][y + 4] = '0';
	world[x + 3][y + 4] = '0';
	world[x + 4][y + 4] = '0';
	world[x + 2][y - 1] = '0';
	world[x + 2][y + 5] = '0';
	world[x + 3][y - 2] = '0';
	world[x + 3][y + 6] = '0';
	world[x - 1][y + 2] = '0';
}

void map::createTable(int x, int y)
{
	world[x + 1][y] = '|';
	world[x + 2][y] = '|';
	world[x][y + 1] = '_';
	world[x + 1][y + 1] = ' ';
	world[x + 2][y + 1] = '_';
	world[x][y + 2] = '_';
	world[x + 1][y + 2] = ' ';
	world[x + 2][y + 2] = '_';
	world[x][y + 3] = '_';
	world[x + 1][y + 3] = ' ';
	world[x + 2][y + 3] = '_';
	world[x + 1][y + 4] = '|';
	world[x + 2][y + 4] = '|';
}

void map::createPondOne(int x, int y)
{
	world[x][y] = ' ';
	world[x + 1][y] = '`';
	world[x + 2][y] = '`';
	world[x + 3][y] = '`';
	world[x + 4][y] = '`';
	world[x + 5][y] = ' ';
	world[x][y + 1] = '`';
	world[x + 1][y + 1] = ' ';
	world[x + 2][y + 1] = '~';
	world[x + 3][y + 1] = ' ';
	world[x + 4][y + 1] = '~';
	world[x + 5][y + 1] = '`';
	world[x][y + 2] = '`';
	world[x + 1][y + 2] = '~';
	world[x + 2][y + 2] = '~';
	world[x + 3][y + 2] = '~';
	world[x + 4][y + 2] = ' ';
	world[x + 5][y + 2] = '`';
	world[x][y + 3] = '`';
	world[x + 1][y + 3] = ' ';
	world[x + 2][y + 3] = ' ';
	world[x + 3][y + 3] = '~';
	world[x + 4][y + 3] = '~';
	world[x + 5][y + 3] = '`';
	world[x][y + 4] = '`';
	world[x + 1][y + 4] = '~';
	world[x + 2][y + 4] = '~';
	world[x + 3][y + 4] = '~';
	world[x + 4][y + 4] = '~';
	world[x + 5][y + 4] = '`';
	world[x][y + 5] = '`';
	world[x + 1][y + 5] = '~';
	world[x + 2][y + 5] = ' ';
	world[x + 3][y + 5] = '~';
	world[x + 4][y + 5] = '~';
	world[x + 5][y + 5] = '`';
	world[x][y + 6] = '`';
	world[x + 1][y + 6] = '~';
	world[x + 2][y + 6] = '~';
	world[x + 3][y + 6] = ' ';
	world[x + 4][y + 6] = '~';
	world[x + 5][y + 6] = '`';
	world[x][y + 7] = '`';
	world[x + 1][y + 7] = '~';
	world[x + 2][y + 7] = '~';
	world[x + 3][y + 7] = '~';
	world[x + 4][y + 7] = '~';
	world[x + 5][y + 7] = '`';
	world[x][y + 8] = ' ';
	world[x + 1][y + 8] = '`';
	world[x + 2][y + 8] = '`';
	world[x + 3][y + 8] = '`';
	world[x + 4][y + 8] = '`';
	world[x + 5][y + 8] = ' ';
}

void map::createPondTwo(int x, int y)
{
	world[x][y] = ' ';
	world[x + 1][y] = '`';
	world[x + 2][y] = '`';
	world[x + 3][y] = '`';
	world[x + 4][y] = '`';
	world[x + 5][y] = ' ';
	world[x][y + 1] = '`';
	world[x + 1][y + 1] = ' ';
	world[x + 2][y + 1] = '~';
	world[x + 3][y + 1] = '~';
	world[x + 4][y + 1] = '~';
	world[x + 5][y + 1] = '`';
	world[x][y + 2] = '`';
	world[x + 1][y + 2] = ' ';
	world[x + 2][y + 2] = '~';
	world[x + 3][y + 2] = '~';
	world[x + 4][y + 2] = '~';
	world[x + 5][y + 2] = '`';
	world[x][y + 3] = '`';
	world[x + 1][y + 3] = '~';
	world[x + 2][y + 3] = ' ';
	world[x + 3][y + 3] = '~';
	world[x + 4][y + 3] = ' ';
	world[x + 5][y + 3] = '`';
	world[x][y + 4] = '`';
	world[x + 1][y + 4] = ' ';
	world[x + 2][y + 4] = '~';
	world[x + 3][y + 4] = ' ';
	world[x + 4][y + 4] = '~';
	world[x + 5][y + 4] = '`';
	world[x][y + 5] = '`';
	world[x + 1][y + 5] = '~';
	world[x + 2][y + 5] = '~';
	world[x + 3][y + 5] = '~';
	world[x + 4][y + 5] = '~';
	world[x + 5][y + 5] = '`';
	world[x][y + 6] = '`';
	world[x + 1][y + 6] = '~';
	world[x + 2][y + 6] = ' ';
	world[x + 3][y + 6] = '~';
	world[x + 4][y + 6] = '~';
	world[x + 5][y + 6] = '`';
	world[x][y + 7] = '`';
	world[x + 1][y + 7] = '~';
	world[x + 2][y + 7] = ' ';
	world[x + 3][y + 7] = '~';
	world[x + 4][y + 7] = '~';
	world[x + 5][y + 7] = '`';
	world[x][y + 8] = ' ';
	world[x + 1][y + 8] = '`';
	world[x + 2][y + 8] = '`';
	world[x + 3][y + 8] = '`';
	world[x + 4][y + 8] = '`';
	world[x + 5][y + 8] = ' ';
}

void map::createBridge(int x, int y)
{
	world[x][y] = '|';
	world[x + 1][y] = '|';
	world[x + 2][y] = '|';
	world[x + 3][y] = '|';
	world[x + 4][y] = '|';
	world[x + 5][y] = '|';
	world[x + 6][y] = '|';
	world[x][y + 1] = ' ';
	world[x + 1][y + 1] = ' ';
	world[x + 2][y + 1] = ' ';
	world[x + 3][y + 1] = ' ';
	world[x + 4][y + 1] = ' ';
	world[x + 5][y + 1] = ' ';
	world[x][y + 2] = ' ';
	world[x + 1][y + 2] = ' ';
	world[x + 2][y + 2] = ' ';
	world[x + 3][y + 2] = ' ';
	world[x + 4][y + 2] = ' ';
	world[x + 5][y + 2] = ' ';
	world[x][y + 3] = ' ';
	world[x + 1][y + 3] = ' ';
	world[x + 2][y + 3] = ' ';
	world[x + 3][y + 3] = ' ';
	world[x + 4][y + 3] = ' ';
	world[x + 5][y + 3] = ' ';
	world[x][y + 4] = '|';
	world[x + 1][y + 4] = '|';
	world[x + 2][y + 4] = '|';
	world[x + 3][y + 4] = '|';
	world[x + 4][y + 4] = '|';
	world[x + 5][y + 4] = '|';
	world[x + 6][y + 4] = '|';
}

void map::createRiver()
{
	int x;
	int y;

	for (x = 6; x < 7; x++)
	{
		for (y = 1; y < 40; y++)
		{
			world[x][y] = '^';
		}
	}
	for (x = 7; x < 10; x++)
	{
		for (y = 1; y < 40; y++)
		{
			world[x][y] = '~';
		}
	}
	for (x = 10; x < 11; x++)
	{
		for (y = 1; y < 40; y++)
		{
			world[x][y] = '^';
		}
	}

	world[7][rand() % + 39] = ' ';
	world[7][rand() % +39] = ' ';
	world[7][rand() % +39] = ' ';
	world[7][rand() % +39] = ' ';
	world[7][rand() % +39] = ' ';
	world[7][rand() % +39] = ' ';
	world[8][rand() % +39] = ' ';
	world[8][rand() % +39] = ' ';
	world[8][rand() % +39] = ' ';
	world[8][rand() % +39] = ' ';
	world[8][rand() % +39] = ' ';
	world[8][rand() % +39] = ' ';
	world[9][rand() % +39] = ' ';
	world[9][rand() % +39] = ' ';
	world[9][rand() % +39] = ' ';
	world[9][rand() % +39] = ' ';
	world[9][rand() % +39] = ' ';
}

void map::createWell(int x, int y)
{
	world[x][y] = ' ';
	world[x + 1][y] = ' ';
	world[x + 2][y] = '=';
	world[x + 3][y] = ' ';
	world[x + 4][y] = ' ';
	world[x][y + 1] = ' ';
	world[x + 1][y + 1] = '=';
	world[x + 2][y + 1] = ' ';
	world[x + 3][y + 1] = '=';
	world[x + 4][y + 1] = ' ';
	world[x][y + 2] = '=';
	world[x + 1][y + 2] = ' ';
	world[x + 2][y + 2] = '~';
	world[x + 3][y + 2] = ' ';
	world[x + 4][y + 2] = '=';
	world[x][y + 3] = '=';
	world[x + 1][y + 3] = '~';
	world[x + 2][y + 3] = ' ';
	world[x + 3][y + 3] = '~';
	world[x + 4][y + 3] = '=';
	world[x][y + 4] = '=';
	world[x + 1][y + 4] = ' ';
	world[x + 2][y + 4] = '~';
	world[x + 3][y + 4] = ' ';
	world[x + 4][y + 4] = '=';
	world[x][y + 5] = '=';
	world[x + 1][y + 5] = '~';
	world[x + 2][y + 5] = ' ';
	world[x + 3][y + 5] = '~';
	world[x + 4][y + 5] = '=';
	world[x][y + 6] = '=';
	world[x + 1][y + 6] = ' ';
	world[x + 2][y + 6] = '~';
	world[x + 3][y + 6] = ' ';
	world[x + 4][y + 6] = '=';
	world[x][y + 7] = ' ';
	world[x + 1][y + 7] = '=';
	world[x + 2][y + 7] = ' ';
	world[x + 3][y + 7] = '=';
	world[x + 4][y + 7] = ' ';
	world[x][y + 8] = ' ';
	world[x + 1][y + 8] = ' ';
	world[x + 2][y + 8] = '=';
	world[x + 3][y + 8] = ' ';
	world[x + 4][y + 8] = ' ';
}

void map::createTent(int x, int y)
{
	world[x + 4][y - 4] = '/';
	world[x + 3][y - 3] = '/';
	world[x + 4][y - 3] = '_';
	world[x + 5][y - 3] = ' ';
	world[x + 2][y - 2] = '/';
	world[x + 4][y - 2] = '_';
	world[x + 1][y - 1] = '/';
	world[x + 4][y - 1] = '_';
	world[x][y] = '_';
	world[x + 4][y] = '_';
	world[x + 5][y] = ' ';
	world[x][y + 1] = '_';
	world[x + 4][y + 1] = '_';
	world[x][y + 2] = '_';
	world[x + 4][y + 2] = '_';
	world[x][y + 3] = '_';
	world[x + 4][y + 3] = '_';
	world[x][y + 4] = '_';
	world[x + 4][y + 4] = '_';
	world[x][y + 5] = '_';
	world[x + 4][y + 5] = '_';
	world[x + 5][y + 5] = ' ';
	world[x][y + 6] = '_';
	world[x + 4][y + 6] = '/';
	world[x][y + 7] = '_';
	world[x + 3][y + 7] = '/';
	world[x + 4][y + 7] = '_';
	world[x][y + 8] = '_';
	world[x + 2][y + 8] = '/';
	world[x + 4][y + 8] = '_';
	world[x][y + 9] = '_';
	world[x + 1][y + 9] = '/';
	world[x + 4][y + 9] = '_';
	world[x + 1][y + 10] = '|';
	world[x + 2][y + 10] = '|';
	world[x + 3][y + 10] = '|';
	world[x + 4][y + 10] = '|';
	world[x + 1][y + 11] = '\\';
	world[x + 4][y + 11] = '_';
	world[x + 5][y + 11] = ' ';
	world[x + 2][y + 12] = '\\';
	world[x + 4][y + 12] = '_';
	world[x + 5][y + 12] = ' ';
	world[x + 3][y + 13] = '\\';
	world[x + 4][y + 13] = '_';
	world[x + 5][y + 13] = ' ';
	world[x + 4][y + 14] = '\\';
}