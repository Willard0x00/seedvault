#include "Engine.h"

#include "Log.h"

#include <iostream>
#include <exception>
#include <thread>

Engine::Engine() :
	m_heartbeat ( 60000 )
{
	Log::get().write(L_SYSTEM, "Engine Starting");
}

Engine::~Engine() {
	Log::get().write(L_SYSTEM, "Engine Shuting Down");
}

int Engine::start() {
	while (!exitCondition()) {

		EngineClock::get().startFrame();
		
		handleStuff();

		doStuff();

		drawStuff();

		analyzeStuff();

		if (m_heartbeat.elapsed()) {
			Log::get().write(L_DEBUG, "...heartbeat...");
		}

		EngineClock::get().endFrame();
	}

	Log::get().write(L_SYSTEM, "Exiting cleanly");
	return 0;
}