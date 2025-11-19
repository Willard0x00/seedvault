#include "Engine.h"

#include <iostream>
#include <exception>

Engine::Engine() {}

Engine::~Engine() {}

bool Engine::mainLoop() {
	while (!exitCondition()) {
		m_frameTimer.update();

		try {
			handleStuff();
		}
		catch (std::exception e) {
			std::cout << "Error handling stuff: " << e.what() << "\n";
			return -1;
		}

		try {
			doStuff();
		}
		catch (std::exception e) {
			std::cout << "Error doing stuff: " << e.what() << "\n";
			return -2;
		}

		try {
			drawStuff();
		}
		catch (std::exception e) {
			std::cout << "Error drawign stuff: " << e.what() << "\n";
			return -3;
		}
	}

	std::cout << "Exiting cleanly" << "\n";
	return 0;
}