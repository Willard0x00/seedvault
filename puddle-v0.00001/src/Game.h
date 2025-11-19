#ifndef GAME_H
#define GAME_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <chrono>

#include "Engine.h"

#include "Camera.h"

#include "ProgramManager.h"
#include "SpriteManager.h"
#include "EntityManager.h"

#include "Map.h"

class Game : public Engine {
public:
	Game(GLFWwindow* window);
	~Game();

	bool exitCondition();

	void handleStuff();

	void doStuff();

	void drawStuff();
private:
	GLFWwindow* m_window;

	Camera m_camera;

	ProgramManager m_programManager;

	SpriteManager m_spriteManager;

	EntityManager m_entityManager;

	Entity* m_player;

	Map m_map;

	std::chrono::system_clock::time_point m_lastFrame;
};

#endif