#ifndef EDITOR_H
#define EDITOR_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Engine.h"

#include "Camera.h"

#include "ProgramManager.h"
#include "SpriteManager.h"
#include "EntityManager.h"

#include "Map.h"
#include "MenuUI.h"
#include "TileUI.h"

class Editor : public Engine {
public:
	Editor(GLFWwindow* window);
	~Editor();

	bool exitCondition();

	void handleStuff();

	void doStuff();

	void drawStuff();

	static void onWindowResize(GLFWwindow* window, int width, int height);

private:
	GLFWwindow* m_window;

	Camera m_camera;

	ProgramManager m_programManager;

	SpriteManager m_spriteManager;

	EntityManager m_entityManager;

	Map m_map;

	MenuUI m_menuUI;

	TileUI m_tileUI;
};

#endif