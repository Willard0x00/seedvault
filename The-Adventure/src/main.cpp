#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
using namespace std;

int main()
{
	int iSelect;
	int rAttack;
	int iHealth;
	int iEnemy;
	int rHealth;
	int iSword;
	int rEnemy;
	int iGold;
	int iSsword;
	int iIsword;
	int iFsword;
	int iIcsword;
	int rGold;
	int iIarmor;
	int iSarmor;
	int iFarmor;
	int iIcarmor;
	int iMihealth;
	int iHealthp;
	int iMhealth;
	int iExpp;
	int iArmor;
	int iExp;
	int iLvl;
	iLvl = 1;
	iExp = 0;
	iArmor = 40;
	iExpp = 0;
	iMhealth = 0;
	iHealthp = 0;
	iMihealth = 0;
	iIarmor = 0;
	iSarmor = 0;
	iFarmor = 0;
	iIcarmor = 0;
	rGold = 0;
	iFsword = 0;
	iIcsword = 0;
	iIsword = 0;
	iSsword = 0;
	iGold = 10000;
	rEnemy = (rand()%2);
	iSword = 25;
	rHealth = (rand()%10);
	iEnemy = 100;
	iHealth = 100;
	rAttack = (rand()%10);
	iSelect = 0;
Main:
	cout << "Welcome adventurer.\n";
	cout << "Where would you like to go\n";
	cout << "1: SnowyMountain\n";
	cin >> iSelect;
	if (iSelect == 1)
	{
		goto Mountains;
	}
	else
	if (iSelect != 1)
	{
		cout << "You didnt type in an acceptable answer please try again. \n";
		system("PAUSE");
		goto Main;
	}
Mountains:
	system("COLOR 3");
	cout << "You walk along a path up the mountain when a snow leapord jumps on you!\n";
	rAttack = (rand()%10);
	cout << "You lose " << rAttack << " Health Points\n";
	iHealth = iHealth - rAttack;
	cout << "Health Points: " << iHealth << endl;
	cout << "Fight the monster or Run away?\n";
	cout << "1: Fight snow Leapord\n";
	cout << "2: Run away from the snow Leapord\n";
	cin >> iSelect;
	if (iSelect == 1)
	{
		goto snowleapord_a;
	}
	else
	if (iSelect == 2)
	{
		cout << "You ran away\n";
		cout << "You contiune along the path and find a town\n";
		system("PAUSE");
		goto stown;
	}
snowleapord_a:
	iEnemy = 50;
snowleapord_b:
	rHealth = (rand()%iArmor);
	iHealth = iHealth - rHealth;
	if (iHealth <= 0)
	{
		cout << "You died\n";
		system("PAUSE");
		return 0;
	}
	else
	cout << "You lost " << rHealth << " Health points.\n";
	cout << "You have " << iHealth << " Health points.\n";
	rAttack = (rand()%iSword);
	iEnemy = iEnemy - rAttack;
	if (iEnemy <= 0)
	{
		cout << "You did " << rAttack << " damage to the snow leapord\n";
		cout << "You killed the snow Leapord!\n";
		rGold = (rand()%50)+2;
		iGold = iGold + rGold;
		cout << "You got " << rGold << " gold\n";
		cout << "You know have " << iGold << " gold\n";
		cout << "You continue along the path and find a town.\n";
		system("PAUSE");
		goto stown;
		goto snowstore;
	}
	else
	cout << "You did " << rAttack << " damage\n";
	cout << "The snow leapord has " << iEnemy << " Health points\n\n";
	system("PAUSE");
	cout << "\n";
	goto snowleapord_b;

	
	system("PAUSE");
	goto Main;
stown:
	cout << " SNOW TOWN\n";
	cout << "1: weapon store\n";
	cout << "2: armor store\n";
	cout << "3: potion store\n";
	cout << "4: inventory\n";
	cin >> iSelect;
	if (iSelect == 1)
	{
		goto wsstore;
	}
	else
	if (iSelect == 2)
	{
		goto asstore;
	}
	else
	if (iSelect == 3)
	{
		goto psstore;
	}
	else
	if (iSelect == 4)
	{
		goto inventory;
	}
	else
	if (iSelect != 1 && iSelect != 2 && iSelect != 3 && iSelect != 4)
	{
		cout << "You didnt type an acceptable answer\n";
		system("PAUSE");
		goto stown;
	}
wsstore:
	cout << " WEAPON STORE \n";
	cout << "1: iron sword      GOLD: 50\n";
	cout << "2: steel sword     GOLD: 150\n";
	cout << "3: fire sword      GOLD: 500\n";
	cout << "4: ice sword       GOLD: 650\n";
	cin >> iSelect;
	if (iSelect == 1)
	{
		if (iGold >= 50)
		{
			iGold = iGold - 50;
			iIsword = iIsword + 1;
			cout << "You bought a iron sword go to your inventory to equip it.\n";
			system("PAUSE");
			goto stown;
		}
		else 
		if (iSelect <= 50)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 2)
	{
		if (iGold >= 150)
		{
			iGold = iGold - 150;
			iSsword = iSsword + 1;
			cout << "You bought a steel sword go to your inventory to equip it.\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 150)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 3)
	{
		if (iGold >= 500)
		{
			iGold = iGold - 500;
			iFsword = iFsword + 1;
			cout << "You bought a fire sword go to your inventory to equip it.\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 500)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 4)
	{
		if (iGold >= 500)
		{
			iGold = iGold - 650;
			iIcsword = iIcsword + 1;
			cout << "You bought a ice sword go to your inventory to equip it.\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 500)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect != 1 && iSelect != 2 && iSelect != 3 && iSelect != 4)
	{
		cout << "You did now type an acceptable answer\n";
		system("PAUSE");
		goto stown;
	}


asstore:
	cout << " ARMOR STORE \n";
	cout << "1: Iron armor      GOLD: 100\n";
	cout << "2: Steel armor     GOLD: 250\n";
	cout << "3: Fire armor      GOLD: 700\n";
	cout << "4: Ice armor       GOLD 750\n";
	cin >> iSelect;
	if (iSelect == 1)
	{
		if (iGold >= 100)
		{
			iGold = iGold - 100;
			iIarmor = 1;
			cout << "You bought iron armor go to your inventory to equip it\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 100)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 2)
	{
		if (iGold >= 250)
		{
			iGold = iGold - 250;
			iSarmor = 1;
			cout << "You bought steel armor go to your inventory to equip it\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 250)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 3)
	{
		if (iGold >= 700)
		{	
			iGold = iGold - 700;
			iFarmor = 1;
			cout << "You bought fire armor go to your inventory to equip it\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 700)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	if (iSelect == 4)
	{
		if (iGold >= 750)
		{	
			iGold = iGold - 750;
			iIcarmor = 1;
			cout << "You bought ice armor go to your inventory to equip it\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 750)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}

psstore:
	cout << " POTION STORE \n";
	cout << "1: minor health potion     GOLD: 50\n";
	cout << "2: health potion           GOLD: 100\n";
	cout << "3: major health potion     GOLD: 200\n";
	cout << "4: experience potion       GOLD: 500\n";
	cin >> iSelect;
	if (iSelect == 1)
	{
		if (iGold >= 50)
		{
			iGold = iGold - 50;
			iMihealth = iMihealth + 1;
			cout << "You bought a minor health potion go to your inventory to use it!\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 50)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 2)
	{
		if (iGold >= 100)
		{
			iGold = iGold - 100;
			iHealthp = iHealthp + 1;
			cout << "You bought a health potion go to your inventory to use it!\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 100)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 3)
	{
		if (iGold >= 200)
		{
			iGold = iGold - 200;
			iMhealth = iMhealth + 1;
			cout << "You bought a major health potion go to your inventory to use it!\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 200)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect == 3)
	{
		if (iGold >= 500)
		{
			iGold = iGold - 500;
			iExpp = iExpp + 1;
			cout << "You bought a experience potion go to your inventory to use it!\n";
			system("PAUSE");
			goto stown;
		}
		else
		if (iGold <= 500)
		{
			cout << "You dont have enough gold go kill more creatures\n";
			system("PAUSE");
			goto stown;
		}
	}
	else
	if (iSelect != 1 && iSelect != 2 && iSelect != 3 && iSelect != 4)
	{
		cout << "You didnt type in an acceptable answer\n";
		system("PAUSE");
		goto stown;
	}
inventory:
	cout << " INVENTORY \n";
	cout << "1: weapons\n";
	cout << "2: armor\n";
	cout << "3: potions\n";
	cin >> iSelect;
	if (iSelect == 1)
	{
			cout << " WEAPONS \n";
			cout << iIsword << " Iron sword        1 to equip\n";
			cout << iSsword << " Steel sword       2 to equip\n";
			cout << iFsword << " Fire sword        3 to equip\n";
			cout << iIcsword << " Ice sword         4 to equip\n";
			cin >> iSelect;
			if (iSelect == 1 && iIsword >= 1)
			{
				iSword = 30;
				cout << "You equiped an iron sword\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 1 && iIsword <= 0)
			{
				cout << "You dont have any iron swords go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 2 && iSsword >= 1)
			{
				iSword = 50;
				cout << "You equiped a steel sword\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 2 && iSsword <= 0)
			{
				cout << "You dont have any steel swords go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 3 && iFsword >= 1)
			{
				iSword = 70;
				cout << "You equiped a fire sword\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 3 && iFsword <= 0)
			{
				cout << "You dont have any fire swords go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 4 && iIcsword >= 1)
			{
				iSword = 100;
				cout << "You equiped an ice sword\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 4 && iIcsword <= 0)
			{
				cout << "You dont have any ice swords go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}

	}
	else
	if (iSelect == 2)
	{
			cout << " ARMOR \n";
			cout << iIarmor << " Iron armor       1 to equip\n";
			cout << iSarmor << " Steel armor      2 to equip\n";
			cout << iFarmor << " Fire armor       3 to equip\n";
			cout << iIcarmor << " Ice armor        4 to equip\n";
			cin >> iSelect;
			if (iSelect == 1 && iIarmor >= 1)
			{
				iArmor = 30;
				cout << "You equiped an iron armor\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 1 && iIarmor <= 0)
			{
				cout << "You dont have any iron armor go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 2 && iSarmor >= 1)
			{
				iArmor = 25;
				cout << "You equiped a steel armor\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 2 && iSarmor <= 0)
			{
				cout << "You dont have any steel armor go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 3 && iFarmor >= 1)
			{
				iSword = 15;
				cout << "You equiped a fire armor\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 3 && iFarmor <= 0)
			{
				cout << "You dont have any fire armor go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 4 && iIcarmor >= 1)
			{
				iSword = 5;
				cout << "You equiped an ice armor\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 4 && iIcarmor <= 0)
			{
				cout << "You dont have any ice armor go to the weapon store to buy one\n";
				system("PAUSE");
				goto stown;
			}
	}
	else
	if (iSelect == 3)
	{
			cout << " POTIONS \n";
			cout << iMihealth << " Minor health potions     1 to use\n";
			cout << iHealthp << " Health potions           2 to use\n";
			cout << iMhealth << " Major health potions     3 to use\n";
			cout << iExpp << " Experience potions         4 to use\n";
			cin >> iSelect;
			if (iSelect == 1 && iMihealth >= 1)
			{
				iHealth = iHealth + 10;
				iMihealth = iMihealth - 1;
				cout << "You used minor health potion!\n";
				cout << "You now have " << iHealth << " Health\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 1 && iMihealth <= 0)
			{
				cout << "You dont have any minor health potions go to the potion store to buy some\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 2 && iHealthp >= 1)
			{
				iHealth = iHealth + 20;
				iHealthp = iHealthp - 1;
				cout << "You used a Health potion\n";
				cout << "You know have " << iHealth << " Health\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 2 && iHealthp <= 0)
			{
				cout << "You dont have any Health potions go to the potion store to buy some\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 3 && iMhealth >= 1)
			{
				iHealth = iHealth + 40;
				iMhealth = iMhealth - 1;
				cout << "You used a major health potion\n";
				cout << "You know have " << iHealth << " Health\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 3 && iMhealth <= 0)
			{
				cout << "You dont have any health potions go to the potion store to buy some\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 4 && iExpp >= 1)
			{
				iExpp = iExpp - 1;
				iExp = iExp + 20;
				if (iExp == 100)
				{
					cout << "You gained a level!!!\n";
					iLvl = iLvl + 1;
					cout << "You are level " << iLvl << " !!!\n";
					system("PAUSE");
					goto stown;
				}
				else
				cout << "You used a experience potion\n";
				system("PAUSE");
				goto stown;
			}
			else
			if (iSelect == 4 && iExpp <= 0)
			{
				cout << "You dont have any experience potions go to the potion store to buy some\n";
				system("PAUSE");
				goto stown;
			}
	}
snowstore:
	system("PAUSE");
	return 0;
}