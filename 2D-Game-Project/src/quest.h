#include <string>

#include "file.h"
#include "options.h"

#ifndef QUEST_H
#define QUEST_H

#define QUEST_KILL_COUNT 1
#define QUEST_TALK 2

class Quest {
private:
public:
	std::string name;
	std::string targetName;
	std::string activeCount;
	u8string npcName;
	u8string question;
	u8string active;
	u8string complete;
	std::vector<u8string> dialoge;

	int id;
	int type;
	int count;
	int total;
	int targetID;
	int rewardID;
	int line;
	int lines;
	bool isComplete;
	bool isActive;
	bool isEnd;

	void Init(const int& npcID);
	void update();
	void nextLine();
	void addCount(const int& enemyID);
};

#endif
