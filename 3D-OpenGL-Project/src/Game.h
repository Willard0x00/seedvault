#include <stdio.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "SystemHandler.h"
#include "InputHandler.h"
#include "ResourceHandler.h"
#include "Renderer.h"
#include "Camera.h"

#ifndef GAME_H
#define GAME_H

class Game {
private:
	System *_system;
	Input *_input;
	ResourceHandler *_resources;
	Renderer *_renderer;
public:
	int Init(
		System *system,
		Input *input,
		ResourceHandler *resources,
		Renderer *renderer
	);
	void begin();
	void input();
	void update();
	void display();
};

#endif