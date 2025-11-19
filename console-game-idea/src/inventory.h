#include <string>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <fstream>
#include "string.h"
#include "item.h"
#include "player.h"

#ifndef INVENTORY_H
#define INVENTORY_H

class inventory
{
private:
	
public:
	static void loadInventory();
	static void updateItemPlayer(item& slot, bool equip);
	static void addItem(int x);
	static void save(bool equip);
	static void load();
	static int bag[20];
};
#endif