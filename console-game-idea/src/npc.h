#include <iostream>
#include <fstream>
#include "player.h"
#include "map.h"

#ifndef NPC_H
#define NPC_H

class npc
{
private:
	int questNum;
	int questKill;
	int questKillT;
	bool quest;
public:
	static void interactNPC(int x);
	static void addKill(int x);
	static void save();
	static void load();
	void setQuestNum(int nquestNum);
	void setQuestKill(int nkill);
	void setQuestKillT(int nkill);
	void setQuest(bool nquest);
	int getQuestNum();
	int getQuestKill();
	int getQuestKillT();
	bool getQuest();
};

#endif