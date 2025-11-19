#ifndef ENGINE_H
#define ENGINE_H

#include "FrameTimer.h"

class Engine {
public:
	Engine();
	~Engine();

	bool mainLoop();

	virtual bool exitCondition() = 0;

	virtual void handleStuff() = 0;

	virtual void doStuff() = 0;

	virtual void drawStuff() = 0;
private:
	FrameTimer m_frameTimer;
};

#endif