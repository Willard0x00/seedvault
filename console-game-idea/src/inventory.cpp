#include "inventory.h"

void loadItems(item& slot, int x);
void showBag();
void showItem(item& slot, int x);
int getInputBag();
void bagUp();
void bagDown();
void equipItem();
void dropItem();
void checkEmptyBag();
void updateSelectionDrop();
void addItemBag(int x, bool& full);
void saveItems(bool equip);
void loadItemAtt();
bool bagFull();
void test2(int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9, int b10, int b11, int b12, int b13, int b14, int b15, int b16, int b17, int b18, int b19, int b20);
void saveBag();
item getSlotId();
std::string checkEquip(item& slot);
std::string checkSpace(int x);
std::string checkSpaceName(item& slot);
std::string checkSpaceStat(int x);
std::string checkSpaceEquip(bool x);
std::string checkSelect(int x);

int bag[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int selection = NULL;
bool exitBag = false;
bool change = true;
bool empty = true;
bool e1 = false;
bool e2 = false;
bool e3 = false;
bool e4 = false;
bool e5 = false;
bool e6 = false;
bool e7 = false;
bool e8 = false;
bool e9 = false;
bool e10 = false;
bool e11 = false;
bool e12 = false;
bool e13 = false;
bool e14 = false;
bool e15 = false;
bool e16 = false;
bool e17 = false;
bool e18 = false;
bool e19 = false;
bool e20 = false;
item slot1;
item slot2;
item slot3;
item slot4;
item slot5;
item slot6;
item slot7;
item slot8;
item slot9;
item slot10;
item slot11;
item slot12;
item slot13;
item slot14;
item slot15;
item slot16;
item slot17;
item slot18;
item slot19;
item slot20;

void inventory::loadInventory()
{
	int input = 0;
	selection = NULL;
	exitBag = false;
	change = true;

	checkEmptyBag();
	loadItemAtt();
	updateSelectionDrop();

	while (exitBag == false)
	{
		showBag();
		change = false;
		input = getInputBag();

		if ((input == 1) & (empty == false))
		{
			equipItem();
			change = true;
		}
		else if ((input == 2) & (empty == false))
		{
			std::cout << "ARE YOU SURE YOU WANT TO DROP THIS?" << std::endl;
			std::cout << "Y/N" << std::endl;
			dropItem();
			change = true;
		}
		else if (input == 4)
		{
			exitBag = true;
		}
		else if ((input == 5) & (empty == false))
		{
			bagUp();
			change = true;
		}
		else if ((input == 6) & (empty == false))
		{
			bagDown();
			change = true;
		}
	}
}

void loadItemAtt()
{
	loadItems(slot1, 0);
	loadItems(slot2, 1);
	loadItems(slot3, 2);
	loadItems(slot4, 3);
	loadItems(slot5, 4);
	loadItems(slot6, 5);
	loadItems(slot7, 6);
	loadItems(slot8, 7);
	loadItems(slot9, 8);
	loadItems(slot10, 9);
	loadItems(slot11, 10);
	loadItems(slot12, 11);
	loadItems(slot13, 12);
	loadItems(slot14, 13);
	loadItems(slot15, 14);
	loadItems(slot16, 15);
	loadItems(slot17, 16);
	loadItems(slot18, 17);
	loadItems(slot19, 18);
	loadItems(slot20, 19);
}

void loadItems(item& slot, int x)
{

	switch (bag[x])
	{
		case 0:
			slot.setItem("", 0, 0, 0, 0, 0, 0);
			break;
		case 1:
			slot.setItem("Small Sword", 0, 1, 0, 0, 0, 0);
			break;
		case 2:
			slot.setItem("Dagger", 0, 1, 0, 1, 0, 0);
			break;
		case 3:
			slot.setItem("Small Shield", 5, 0, 1, 0, 0, 0);
			break;
		case 4:
			slot.setItem("Small Bow", 0, 2, 0, 0, 1, 0);
			break;
		case 5:
			slot.setItem("Small Helmet", 10, 0, 1, 0, 0, 0);
			break;
		case 6:
			slot.setItem("Leather Boots", 10, 0, 0, 1, 0, 0);
			break;
		case 7:
			slot.setItem("Necklace", 20, 0, 0, 0, 2, 0);
			break;
		case 8:
			slot.setItem("Ring", 10, 0, 0, 1, 2, 0);
			break;
		case 9:
			slot.setItem("Earring", 5, 0, 0, 2, 2, 0);
			break;
		case 10:
			slot.setItem("Zaimak's Septer", 50, 5, 3, 2, 2, 0);
			break;
		case 99:
			slot.setItem("Milk", 1000, 1000, 1000, 1000, 1000, 0);
			break;
		default:
			slot.setItem("", 0, 0, 0, 0, 0, 0);
			break;
	}
}

void showBag()
{
	if (change == true)
	{
		system("CLS");
		std::cout << "----------------------------------------------------------" << "Bag" << "----------------------------------------------------------" << std::endl;
		std::cout << "Slot                  Equipped        +Health           +Attack            +Defense         +Luck           +Speed" << std::endl;
		showItem(slot1, 1);
		showItem(slot2, 2);
		showItem(slot3, 3);
		showItem(slot4, 4);
		showItem(slot5, 5);
		showItem(slot6, 6);
		showItem(slot7, 7);
		showItem(slot8, 8);
		showItem(slot9, 9);
		showItem(slot10, 10);
		showItem(slot11, 11);
		showItem(slot12, 12);
		showItem(slot13, 13);
		showItem(slot14, 14);
		showItem(slot15, 15);
		showItem(slot16, 16);
		showItem(slot17, 17);
		showItem(slot18, 18);
		showItem(slot19, 19);
		showItem(slot20, 20);
		std::cout << "1. Equip/Unequip" << std::endl;
		std::cout << "2. Drop" << std::endl;
		std::cout << "q: Exit" << std::endl;
		std::cout << selection;
	}
}

void showItem(item& slot, int x)
{
	
	if (slot.getName() == "")
	{

	}
	else
	{
		std::cout << checkSelect(x - 1) << " " << x << ": " << checkSpace(x) << slot.getName() << checkSpaceName(slot) << checkEquip(slot) << checkSpaceEquip(slot.getEquip()) << "             " << slot.getHealth() << checkSpaceStat(slot.getHealth()) << "              " << slot.getAttack() << checkSpaceStat(slot.getAttack()) << "               " << slot.getDefense() << checkSpaceStat(slot.getDefense()) << "             " << slot.getLuck() << checkSpaceStat(slot.getLuck()) << "            " << slot.getSpeed() << std::endl;
	}
}

void bagUp()
{
	if (selection == 0)
	{
		selection = 19;
		if (bag[selection] == 0)
		{
			bagUp();
		}
		showBag();
	}
	else
	{
		selection--;
		if (bag[selection] == 0)
		{
			bagUp();
		}
		showBag();
	}
}

void bagDown()
{
	if (selection == 19)
	{
		selection = 0;
		if (bag[selection] == 0)
		{
			bagDown();
		}
		showBag();
	}
	else
	{
		selection++;
		if (bag[selection] == 0)
		{
			bagDown();
		}
		showBag();
	}
}

std::string checkSpace(int x)
{
	if (x > 9)
	{
		return "";
	}
	else
	{
		return " ";
	}
}

std::string checkSpaceEquip(bool x)
{
	if (x == true)
	{
		return "";
	}
	else if (x == false)
	{
		return " ";
	}
	return "";
}

std::string checkSpaceStat(int x)
{
	if (x > 999)
	{
		return "";
	}
	if (x > 99)
	{
		return " ";
	}
	else if (x > 9)
	{
		return "  ";
	}
	else
	{
		return "   ";
	}
}

std::string checkSpaceName(item& slot)
{
	int x = 0;
	x = slot.getName().length();

	switch (x)
	{
	case 1:
		return "               ";
	case 2:
		return "              ";
	case 3:
		return "             ";
	case 4:
		return "            ";
	case 5:
		return "           ";
	case 6:
		return "          ";
	case 7:
		return "         ";
	case 8: 
		return "        ";
	case 9:
		return "       ";
	case 10:
		return "      ";
	case 11:
		return "     ";
	case 12: 
		return "    ";
	case 13:
		return "   ";
	case 14:
		return "  ";
	case 15:
		return " ";
	default:
		return "";
	}
}

std::string checkEquip(item& slot)
{
	if (slot.getEquip() == false)
	{
		return "no";
	}
	else
	{
		return "yes";
	}
}

std::string checkSelect(int x)
{
	if (x == selection)
	{
		return "*";
	}
	else
	{
		return " ";
	}
}

int getInputBag()
{
	char key = ' ';

	key = _getch();

	switch (key)
	{
	case '1':
		return 1;
	case '2':
		return 2;
	case 'q':
		return 4;
	case 'w':
		return 5;
	case 's':
		return 6;
	default:
		getInputBag();
		break;
	}

	return 0;
}

void equipItem()
{
	switch (selection)
	{
	case 0:
		if (slot1.getEquip() == false) { slot1.setEquip(true); inventory::updateItemPlayer(slot1, true); } else { slot1.setEquip(false); inventory::updateItemPlayer(slot1, false); }
		break;
	case 1:
		if (slot2.getEquip() == false) { slot2.setEquip(true); inventory::updateItemPlayer(slot2, true); } else	{ slot2.setEquip(false); inventory::updateItemPlayer(slot2, false); }
		break;
	case 2:
		if (slot3.getEquip() == false) { slot3.setEquip(true); inventory::updateItemPlayer(slot3, true); } else	{ slot3.setEquip(false); inventory::updateItemPlayer(slot3, false); }
		break;
	case 3:
		if (slot4.getEquip() == false) { slot4.setEquip(true); inventory::updateItemPlayer(slot4, true); } else	{ slot4.setEquip(false); inventory::updateItemPlayer(slot4, false); }
		break;
	case 4:
		if (slot5.getEquip() == false) { slot5.setEquip(true); inventory::updateItemPlayer(slot5, true); } else	{ slot5.setEquip(false); inventory::updateItemPlayer(slot5, false); }
		break;
	case 5:
		if (slot6.getEquip() == false) { slot6.setEquip(true); inventory::updateItemPlayer(slot6, true); } else	{ slot6.setEquip(false); inventory::updateItemPlayer(slot6, false); }
		break;
	case 6:
		if (slot7.getEquip() == false) { slot7.setEquip(true); inventory::updateItemPlayer(slot7, true); } else	{ slot7.setEquip(false); inventory::updateItemPlayer(slot7, false); }
		break;
	case 7:
		if (slot8.getEquip() == false) { slot8.setEquip(true); inventory::updateItemPlayer(slot8, true); } else	{ slot8.setEquip(false); inventory::updateItemPlayer(slot8, false); }
		break;
	case 8:
		if (slot9.getEquip() == false) { slot9.setEquip(true); inventory::updateItemPlayer(slot9, true); } else	{ slot9.setEquip(false); inventory::updateItemPlayer(slot9, false); }
		break;
	case 9:
		if (slot10.getEquip() == false) { slot10.setEquip(true); inventory::updateItemPlayer(slot10, true); } else	{ slot10.setEquip(false); inventory::updateItemPlayer(slot10, false); }
		break;
	case 10:
		if (slot11.getEquip() == false) { slot11.setEquip(true); inventory::updateItemPlayer(slot11, true); } else	{ slot11.setEquip(false); inventory::updateItemPlayer(slot11, false); }
		break;
	case 11:
		if (slot12.getEquip() == false) { slot12.setEquip(true); inventory::updateItemPlayer(slot12, true); } else	{ slot12.setEquip(false); inventory::updateItemPlayer(slot12, false); }
		break;
	case 12:
		if (slot13.getEquip() == false) { slot13.setEquip(true); inventory::updateItemPlayer(slot13, true); } else	{ slot13.setEquip(false); inventory::updateItemPlayer(slot13, false); }
		break;
	case 13:
		if (slot14.getEquip() == false) { slot14.setEquip(true); inventory::updateItemPlayer(slot14, true); } else	{ slot14.setEquip(false); inventory::updateItemPlayer(slot14, false); }
		break;
	case 14:
		if (slot15.getEquip() == false) { slot15.setEquip(true); inventory::updateItemPlayer(slot15, true); } else	{ slot15.setEquip(false); inventory::updateItemPlayer(slot15, false); }
		break;
	case 15:
		if (slot16.getEquip() == false) { slot16.setEquip(true); inventory::updateItemPlayer(slot16, true); } else	{ slot16.setEquip(false); inventory::updateItemPlayer(slot16, false); }
		break;
	case 16:
		if (slot17.getEquip() == false) { slot17.setEquip(true); inventory::updateItemPlayer(slot17, true); } else	{ slot17.setEquip(false); inventory::updateItemPlayer(slot17, false); }
		break;
	case 17:
		if (slot18.getEquip() == false) { slot18.setEquip(true); inventory::updateItemPlayer(slot18, true); } else	{ slot18.setEquip(false); inventory::updateItemPlayer(slot18, false); }
		break;
	case 18:
		if (slot19.getEquip() == false) { slot19.setEquip(true); inventory::updateItemPlayer(slot19, true); } else	{ slot19.setEquip(false); inventory::updateItemPlayer(slot19, false); }
		break;
	case 19:
		if (slot20.getEquip() == false) { slot20.setEquip(true); inventory::updateItemPlayer(slot20, true); } else	{ slot20.setEquip(false); inventory::updateItemPlayer(slot20, false); }
		break;
	default:
		break;
	}
}

void dropItem()
{
	char key = ' ';
	item slot;

	key = _getch();

	switch (key)
	{
	case 'y':
		slot = getSlotId();
		if (slot.getEquip() == true)
		{
			equipItem();
		}
		bag[selection] = 0;
		updateSelectionDrop();
		inventory::loadInventory();
		
	case 'n':
		break;
	default:
		dropItem();
	}

}

void checkEmptyBag()
{
	int x = 0;
	int sum = 0;

	for (x = 0; x < 20; x++)
	{
		sum = sum + bag[x];
	}

	if (sum == 0)
	{
		empty = true;
	}
	else
	{
		empty = false;
	}
}

void updateSelectionDrop()
{

	checkEmptyBag();
	if (empty == true)
	{

	}
	else if (empty == false)
	{
		selection = 0;
		while (bag[selection] == 0)
		{
			selection++;
			checkEmptyBag();
			if (empty == true)
			{
				break;
			}
		}
	}
}

//ITEM STAT UPDATE

void inventory::updateItemPlayer(item& slot, bool equip)
{
	player player;

	if (equip == true)
	{
		player.setHealth(player.getHealth() + slot.getHealth());
		player.setPlayer((player.getMaxHealth() + slot.getHealth()), (player.getAttack() + slot.getAttack()), (player.getDefense() + slot.getDefense()), (player.getSpeed() + slot.getSpeed()), (player.getLuck() + slot.getLuck()));
	}
	else if (equip == false)
	{
		player.setHealth(player.getHealth() - slot.getHealth());
		if (player.getHealth() < 1)
		{
			player.setHealth(1);
		}
		player.setPlayer((player.getMaxHealth() - slot.getHealth()), (player.getAttack() - slot.getAttack()), (player.getDefense() - slot.getDefense()), (player.getSpeed() - slot.getSpeed()), (player.getLuck() - slot.getLuck()));
	}
}

item getSlotId()
{
	switch (selection)
	{
	case 0:
		return slot1;
		break;
	case 1:
		return slot2;
		break;
	case 2:
		return slot3;
		break;
	case 3:
		return slot4;
		break;
	case 4:
		return slot5;
		break;
	case 5:
		return slot6;
		break;
	case 6:
		return slot7;
		break;
	case 7:
		return slot8;
		break;
	case 8:
		return slot9;
		break;
	case 9:
		return slot10;
		break;
	case 10:
		return slot11;
		break;
	case 11:
		return slot12;
		break;
	case 12:
		return slot13;
		break;
	case 13:
		return slot14;
		break;
	case 14:
		return slot15;
		break;
	case 15:
		return slot16;
		break;
	case 16:
		return slot17;
		break;
	case 17:
		return slot18;
		break;
	case 18:
		return slot19;
		break;
	case 19:
		return slot20;
		break;
	default:
		break;
	}
	return slot1;
}

void inventory::addItem(int x)
{
	item slot;
	bool full = false;
	addItemBag(x, full);
	slot = getSlotId();
	if (full == false)
	{
		loadItems(slot, selection);
		std::cout << slot.getName() << " dropped" << std::endl;
		system("PAUSE");
	}
}

void addItemBag(int x, bool& full)
{
	selection = 0;
	while (bag[selection] > 0)
	{
		selection++;
		if (selection == 20)
		{
			full = bagFull();
			break;
		}
	}
	if (full == false)
	{
		bag[selection] = x;
	}

}

bool bagFull()
{

	std::cout << "Your bag is full" << std::endl;
	selection = 0;

	return true;
}

void test2(int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9, int b10, int b11, int b12, int b13, int b14, int b15, int b16, int b17, int b18, int b19, int b20)
{
	bag[0] = b1;
	bag[1] = b2;
	bag[2] = b3;
	bag[3] = b4;
	bag[4] = b5;
	bag[5] = b6;
	bag[6] = b7;
	bag[7] = b8;
	bag[8] = b9;
	bag[9] = b10;
	bag[10] = b11;
	bag[11] = b12;
	bag[12] = b13;
	bag[13] = b14;
	bag[14] = b15;
	bag[15] = b16;
	bag[16] = b17;
	bag[17] = b18;
	bag[18] = b19;
	bag[19] = b20;
}

void inventory::load()
{
	std::ifstream loadfile;
	int b1;
	int b2;
	int b3;
	int b4;
	int b5;
	int b6;
	int b7;
	int b8;
	int b9;
	int b10;
	int b11;
	int b12;
	int b13;
	int b14;
	int b15;
	int b16;
	int b17;
	int b18;
	int b19;
	int b20;
	bool bo1;
	bool bo2;
	bool bo3;
	bool bo4;
	bool bo5;
	bool bo6;
	bool bo7;
	bool bo8;
	bool bo9;
	bool bo10;
	bool bo11;
	bool bo12;
	bool bo13;
	bool bo14;
	bool bo15;
	bool bo16;
	bool bo17;
	bool bo18;
	bool bo19;
	bool bo20;


	loadfile.open("bag.txt");
	loadfile >> b1 >> bo1 >> b2 >> bo2 >> b3 >> bo3 >> b4 >> bo4 >> b5 >> bo5 >> b6 >> bo6 >> b7 >> bo7 >> b8 >> bo8 >> b9 >> bo9 >> b10 >> bo10 >> b11 >> bo11 >> b12 >> bo12 >> b13 >> bo13 >> b14 >> bo14 >> b15 >> bo15 >> b16 >> bo16 >> b17 >> bo17 >> b18 >> bo18 >> b19 >> bo19 >> b20 >> bo20;
	loadfile.close();

	test2(b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16, b17, b18, b19, b20);
	slot1.setEquip(bo1);
	slot2.setEquip(bo2);
	slot3.setEquip(bo3);
	slot4.setEquip(bo4);
	slot5.setEquip(bo5);
	slot6.setEquip(bo6);
	slot7.setEquip(bo7);
	slot8.setEquip(bo8);
	slot9.setEquip(bo9);
	slot10.setEquip(bo10);
	slot11.setEquip(bo11);
	slot12.setEquip(bo12);
	slot13.setEquip(bo13);
	slot14.setEquip(bo14);
	slot15.setEquip(bo15);
	slot16.setEquip(bo16);
	slot17.setEquip(bo17);
	slot18.setEquip(bo18);
	slot19.setEquip(bo19);
	slot20.setEquip(bo20);


	loadItemAtt();
	if (slot1.getEquip() == true)
	{
		inventory::updateItemPlayer(slot1, true);
	}
	if (slot2.getEquip() == true)
	{
		inventory::updateItemPlayer(slot2, true);
	}
	if (slot3.getEquip() == true)
	{
		inventory::updateItemPlayer(slot3, true);
	}
	if (slot4.getEquip() == true)
	{
		inventory::updateItemPlayer(slot4, true);
	}
	if (slot5.getEquip() == true)
	{
		inventory::updateItemPlayer(slot5, true);
	}
	if (slot6.getEquip() == true)
	{
		inventory::updateItemPlayer(slot6, true);
	}
	if (slot7.getEquip() == true)
	{
		inventory::updateItemPlayer(slot7, true);
	}
	if (slot8.getEquip() == true)
	{
		inventory::updateItemPlayer(slot8, true);
	}
	if (slot9.getEquip() == true)
	{
		inventory::updateItemPlayer(slot9, true);
	}
	if (slot10.getEquip() == true)
	{
		inventory::updateItemPlayer(slot10, true);
	}
	if (slot11.getEquip() == true)
	{
		inventory::updateItemPlayer(slot11, true);
	}
	if (slot12.getEquip() == true)
	{
		inventory::updateItemPlayer(slot12, true);
	}
	if (slot13.getEquip() == true)
	{
		inventory::updateItemPlayer(slot13, true);
	}
	if (slot14.getEquip() == true)
	{
		inventory::updateItemPlayer(slot14, true);
	}
	if (slot15.getEquip() == true)
	{
		inventory::updateItemPlayer(slot15, true);
	}
	if (slot16.getEquip() == true)
	{
		inventory::updateItemPlayer(slot16, true);
	}
	if (slot17.getEquip() == true)
	{
		inventory::updateItemPlayer(slot17, true);
	}
	if (slot18.getEquip() == true)
	{
		inventory::updateItemPlayer(slot18, true);
	}
	if (slot19.getEquip() == true)
	{
		inventory::updateItemPlayer(slot19, true);
	}
	if (slot20.getEquip() == true)
	{
		inventory::updateItemPlayer(slot20, true);
	}

}

void inventory::save(bool equip)
{
	saveItems(equip);
	saveBag();
}

void saveBag()
{
	std::ofstream savefile;

	savefile.open("bag.txt");
	savefile << bag[0] << " " << slot1.getEquip() << " " << bag[1] << " " << slot2.getEquip() << " " << bag[2] << " " << slot3.getEquip() << " " << bag[3] << " " << slot4.getEquip() << " " << bag[4] << " " << slot5.getEquip() << " " << bag[5] << " " << slot6.getEquip() << " " << bag[6] << " " << slot7.getEquip() << " " << bag[7] << " " << slot8.getEquip() << " " << bag[8] << " " << slot9.getEquip() << " " << bag[9] << " " << slot10.getEquip() << " " << bag[10] << " " << slot11.getEquip() << " " << bag[11] << " " << slot12.getEquip() << " " << bag[12] << " " << slot13.getEquip() << " " << bag[13] << " " << slot14.getEquip() << " " << bag[14] << " " << slot15.getEquip() << " " << bag[15] << " " << slot16.getEquip() << " " << bag[16] << " " << slot17.getEquip() << " " << bag[17] << " " << slot18.getEquip() << " " << bag[18] << " " << slot19.getEquip() << " " << bag[19] << " " << slot20.getEquip();

	savefile.close();
}

void saveItems(bool equip)
{
	if (equip == false)
	{
		if (slot1.getEquip() == true)
		{
			selection = 0;
			inventory::updateItemPlayer(slot1, false);
			e1 = true;
		}
		if (slot2.getEquip() == true)
		{
			selection = 1;
			inventory::updateItemPlayer(slot2, false);
			e2 = true;
		}
		if (slot3.getEquip() == true)
		{
			selection = 2;
			inventory::updateItemPlayer(slot3, false);
			e3 = true;
		}
		if (slot4.getEquip() == true)
		{
			selection = 3;
			inventory::updateItemPlayer(slot4, false);
			e4 = true;
		}
		if (slot5.getEquip() == true)
		{
			selection = 4;
			inventory::updateItemPlayer(slot5, false);
			e5 = true;
		}
		if (slot6.getEquip() == true)
		{
			selection = 5;
			inventory::updateItemPlayer(slot6, false);
			e6 = true;
		}
		if (slot7.getEquip() == true)
		{
			selection = 6;
			inventory::updateItemPlayer(slot7, false);
			e7 = true;
		}
		if (slot8.getEquip() == true)
		{
			selection = 7;
			inventory::updateItemPlayer(slot8, false);
			e8 = true;
		}
		if (slot9.getEquip() == true)
		{
			selection = 8;
			inventory::updateItemPlayer(slot9, false);
			e9 = true;
		}
		if (slot10.getEquip() == true)
		{
			selection = 9;
			inventory::updateItemPlayer(slot10, false);
			e10 = true;
		}
		if (slot11.getEquip() == true)
		{
			selection = 10;
			inventory::updateItemPlayer(slot11, false);
			e11 = true;
		}
		if (slot12.getEquip() == true)
		{
			selection = 11;
			inventory::updateItemPlayer(slot12, false);
			e12 = true;
		}
		if (slot13.getEquip() == true)
		{
			selection = 12;
			inventory::updateItemPlayer(slot13, false);
			e13 = true;
		}
		if (slot14.getEquip() == true)
		{
			selection = 13;
			inventory::updateItemPlayer(slot14, false);
			e14 = true;
		}
		if (slot15.getEquip() == true)
		{
			selection = 14;
			inventory::updateItemPlayer(slot15, false);
			e15 = true;
		}
		if (slot16.getEquip() == true)
		{
			selection = 15;
			inventory::updateItemPlayer(slot16, false);
			e16 = true;
		}
		if (slot17.getEquip() == true)
		{
			selection = 16;
			inventory::updateItemPlayer(slot17, false);
			e17 = true;
		}
		if (slot18.getEquip() == true)
		{
			selection = 17;
			inventory::updateItemPlayer(slot18, false);
			e18 = true;
		}
		if (slot19.getEquip() == true)
		{
			selection = 18;
			inventory::updateItemPlayer(slot19, false);
			e19 = true;
		}
		if (slot20.getEquip() == true)
		{
			selection = 19;
			inventory::updateItemPlayer(slot20, false);
			e20 = true;
		}

	}
	else if (equip == true)
	{
		if (e1 == true)
		{
			selection = 0;
			inventory::updateItemPlayer(slot1, true);
			e1 = false;
		}
		if (e2 == true)
		{
			selection = 1;
			inventory::updateItemPlayer(slot2, true);
			e2 = false;
		}
		if (e3 == true)
		{
			selection = 2;
			inventory::updateItemPlayer(slot3, true);
			e3 = false;
		}
		if (e4 == true)
		{
			selection = 3;
			inventory::updateItemPlayer(slot4, true);
			e4 = false;
		}
		if (e5 == true)
		{
			selection = 4;
			inventory::updateItemPlayer(slot5, true);
			e5 = false;
		}
		if (e6 == true)
		{
			selection = 5;
			inventory::updateItemPlayer(slot6, true);
			e6 = false;
		}
		if (e7 == true)
		{
			selection = 6;
			inventory::updateItemPlayer(slot7, true);
			e7 = false;
		}
		if (e8 == true)
		{
			selection = 7;
			inventory::updateItemPlayer(slot8, true);
			e8 = false;
		}
		if (e9 == true)
		{
			selection = 8;
			inventory::updateItemPlayer(slot9, true);
			e9 = false;
		}
		if (e10 == true)
		{
			selection = 9;
			inventory::updateItemPlayer(slot10, true);
			e10 = false;
		}
		if (e11 == true)
		{
			selection = 10;
			inventory::updateItemPlayer(slot11, true);
			e11 = false;
		}
		if (e12 == true)
		{
			selection = 11;
			inventory::updateItemPlayer(slot12, true);
			e12 = false;
		}
		if (e13 == true)
		{
			selection = 12;
			inventory::updateItemPlayer(slot13, true);
			e13 = false;
		}
		if (e14 == true)
		{
			selection = 13;
			inventory::updateItemPlayer(slot14, true);
			e14 = false;
		}
		if (e15 == true)
		{
			selection = 14;
			inventory::updateItemPlayer(slot15, true);
			e15 = false;
		}
		if (e16 == true)
		{
			selection = 15;
			inventory::updateItemPlayer(slot16, true);
			e16 = false;
		}
		if (e17 == true)
		{
			selection = 16;
			inventory::updateItemPlayer(slot17, true);
			e17 = false;
		}
		if (e18 == true)
		{
			selection = 17;
			inventory::updateItemPlayer(slot18, true);
			e18 = false;
		}
		if (e19 == true)
		{
			selection = 18;
			inventory::updateItemPlayer(slot19, true);
			e19 = false;
		}
		if (e20 == true)
		{
			selection = 19;
			inventory::updateItemPlayer(slot20, true);
			e20 = false;
		}
	}

}