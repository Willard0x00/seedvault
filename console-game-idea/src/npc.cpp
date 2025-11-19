#include "npc.h"

void loadNPC(int x);
void addKillQuest(npc& quest);
void initQuestT();
void npc0();
void npc1();
void npc2();
void npc3();
void npc4();
void npc5();
void npc6();
void npc7();
void selectQuest(int x);

npc quest1;
npc quest2;
npc quest3;
npc quest4;
npc quest5;

bool first = true;

void npc::interactNPC(int x)
{
	initQuestT();
	loadNPC(x);
}

void initQuestT()
{
	if (first = true)
	{
		quest1.setQuestKillT(10);
		quest2.setQuestKillT(5);
		first = false;
	}
}
void loadNPC(int x)
{

	switch (x)
	{
	case 0:
		npc0();
		break;
	case 1:
		npc1();
		break;
	case 2:
		npc2();
		break;
	case 3:
		npc3();
		break;
	case 4:
		npc4();
		break;
	case 5:
		npc5();
		break;
	case 6: 
		npc6();
		break;
	case 7:
		npc7();
		break;
	}
}

void npc0()
{
	std::cout << "--------------------Old Man--------------------" << std::endl;
	std::cout << "Hello my name is Old Man " << std::endl;
	std::cout << "I am old and out of life" << std::endl;
	std::cout << "I have nothing to give but my knowledge" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "W - Move Up" << std::endl;
	std::cout << "A - Move Left" << std::endl;
	std::cout << "S - Move Down" << std::endl;
	std::cout << "D - Move Right" << std::endl;
	std::cout << "Q - Open Bag" << std::endl;
	std::cout << "E - Open Stats" << std::endl;
	std::cout << "Z - Save Game" << std::endl;
}

void npc1()
{
	player player;

	std::cout << "--------------------Leon--------------------" << std::endl;
	if (quest1.getQuest() == false)
	{
		std::cout << "Quest: Slay Goblins" << std::endl;
		std::cout << "Can you kill the Goblins in the Forest for me?" << std::endl;
		std::cout << "Kill 10 Goblins for me" << std::endl;
		quest1.setQuest(true);
		quest1.setQuestKill(0);
	}
	else if (quest1.getQuest() == true)
	{
		if (quest1.getQuestKill() >= quest1.getQuestKillT())
		{
			std::cout << "Thank you for killing those Goblins" << std::endl;
			std::cout << "Here is 10 Gold" << std::endl;
			player.setGold(player.getGold() + 10);
			quest1.setQuest(false);
			quest1.setQuestKill(0);
		}
		else
		{
			std::cout << "Quest: Slay Goblins" << std::endl;
			std::cout << "You have killed " << quest1.getQuestKill() << " Goblins so far" << std::endl;
			std::cout << "You need to kill " << quest1.getQuestKillT() << " more" << std::endl;
		}
	}

}

void npc2()
{
	player player;

	std::cout << "--------------------Bridge Guard--------------------" << std::endl;
	if (player.getGold() < 10)
	{
		std::cout << "If you want to cross this bridge bring me 10 gold" << std::endl;
	}
	else
	{
		std::cout << "You give the Bridge Guard 10 gold to cross" << std::endl;
		player.setGold(player.getGold() - 10);
		if (player.getX() == 9)
		{
			player.setX(7);
		}
		else if (player.getX() == 7)
		{
			player.setX(9);
		}

	}
}

void npc3()
{
	player player;

	std::cout << "--------------------Gary--------------------" << std::endl;
	if (quest2.getQuest() == false)
	{
		std::cout << "Quest: Slay Bandits" << std::endl;
		std::cout << "There are Bandits North of here hidding in bushes" << std::endl;
		std::cout << "Kill 5 of them for me and I will give you 20 gold" << std::endl;
		quest2.setQuest(true);
		quest2.setQuestKill(0);
	}
	else if (quest2.getQuest() == true)
	{
		if (quest2.getQuestKill() >= quest2.getQuestKillT())
		{
			std::cout << "Thank you for killing those Bandits" << std::endl;
			std::cout << "Here is 20 Gold" << std::endl;
			player.setGold(player.getGold() + 20);
			quest2.setQuest(false);
			quest2.setQuestKill(0);
		}
		else
		{
			std::cout << "Quest: Slay Bandits" << std::endl;
			std::cout << "You have killed " << quest2.getQuestKill() << " Bandits so far" << std::endl;
			std::cout << "You need to kill " << quest2.getQuestKillT() << " more" << std::endl;
		}
	}
}

void npc4()
{
	std::cout << "--------------------Lilo--------------------" << std::endl;
	std::cout << "What are you doing in my house?" << std::endl;
	std::cout << "GET OUT" << std::endl;
}

void npc5()
{
	std::cout << "--------------------Yande--------------------" << std::endl;
	std::cout << "The town is west from here" << std::endl;
	std::cout << "If you need gold go see gary" << std::endl;
	std::cout << "He is hiding in his house in the north part of town" << std::endl;
}

void npc6()
{
	std::cout << "--------------------Jacob--------------------" << std::endl;
	std::cout << "Becareful this tent is magical" << std::endl;
	std::cout << "It's size fools you from the outside" << std::endl;
}

void npc7()
{
	std::cout << "--------------------Small Piece of Paper--------------------" << std::endl;
	std::cout << "2.3.1" << std::endl;
}

void npc::addKill(int x)
{
	selectQuest(x);
}

void addKillQuest(npc& quest)
{

	if (quest.getQuest() == true)
	{
		quest.setQuestKill(quest.getQuestKill() + 1);
	}
	
}

void selectQuest(int x)
{
	switch (x)
	{
	case 1:
		addKillQuest(quest1);
		break;
	case 2:
		addKillQuest(quest2);
		break;
	case 3:
		addKillQuest(quest3);
		break;
	case 4:
		addKillQuest(quest4);
		break;
	case 5:
		addKillQuest(quest5);
		break;
	}
}

void npc::save()
{
	std::ofstream savefile;

	savefile.open("quest.txt");

	savefile << quest1.getQuest() << " " << quest1.getQuestKill() << " " << quest2.getQuest() << " " << quest2.getQuestKill() << " " << quest3.getQuest() << " " << quest3.getQuestKill() << " " << quest4.getQuest() << " " << quest4.getQuestKill() << " " << quest5.getQuest() << " " << quest5.getQuestKill() << " ";

	savefile.close();
}

void npc::load()
{
	std::ifstream loadfile;
	bool q1;
	bool q2;
	bool q3;
	bool q4;
	bool q5;
	int k1;
	int k2;
	int k3;
	int k4;
	int k5;

	loadfile.open("quest.txt");
	loadfile >> q1 >> k1 >> q2 >> k2 >> q3 >> k3 >> q4 >> k4 >> q5 >> k5;
	loadfile.close();

	quest1.setQuest(q1);
	quest2.setQuest(q2);
	quest3.setQuest(q3);
	quest4.setQuest(q4);
	quest5.setQuest(q5);
	quest1.setQuestKill(k1);
	quest2.setQuestKill(k2);
	quest3.setQuestKill(k3);
	quest4.setQuestKill(k4);
	quest5.setQuestKill(k5);
}

void npc::setQuestNum(int nquestNum) { questNum = nquestNum; }
void npc::setQuestKill(int nkill) { questKill = nkill; }
void npc::setQuestKillT(int nkill) { questKillT = nkill; }
void npc::setQuest(bool nquest) { quest = nquest; }
int npc::getQuestNum() { return questNum; }
int npc::getQuestKill() { return questKill; }
int npc::getQuestKillT() { return questKillT; }
bool npc::getQuest() { return quest; }