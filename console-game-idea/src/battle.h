#include <string>
#include <conio.h>
#include "enemy.h"
#include "map.h"
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "npc.h"

#ifndef BATTLE_H
#define BATTLE_H

class battle
{

private:
	bool fight;
public:
	static void battleEnemy(int nenemyid);
};
#endif