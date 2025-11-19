#ifndef ENGINE_H
#define ENGINE_H

#include "EngineClock.h"
#include "Timer.h"

#include <thread>

class Engine {
public:
	Engine();
	~Engine();

	int start();

	virtual bool exitCondition() = 0;

	virtual void handleStuff() = 0;

	virtual void doStuff() = 0;

	virtual void drawStuff() = 0;

	virtual void analyzeStuff() = 0;
protected:
	Timer m_heartbeat;
};

#endif