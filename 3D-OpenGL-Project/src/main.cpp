#include <stdio.h>

#include "SystemHandler.h"
#include "InputHandler.h"
#include "ResourceHandler.h"
#include "Renderer.h"
#include "Game.h"

#include "RenderObject.h"

int main() {
	int exitCode = 0;
	printf("---------------------\n");

	System system;
	exitCode = system.Init(4, 4, GL_TRUE);
	printf("System Exit Code - %d\n", exitCode);

	ResourceHandler resources;
	exitCode = resources.Init();
	printf("Resource Handler Exit Code - %d\n", exitCode);

	Input input;
	exitCode = input.Init(&system, &resources);
	printf("Input Exit Code - %d\n", exitCode);

	Renderer renderer;
	exitCode = renderer.Init(&resources);
	printf("Renderer Exit Code - %d\n", exitCode);

	Game game;
	exitCode = game.Init(&system, &input, &resources, &renderer);
	printf("Game Exit Code - %d\n", exitCode);

	game.begin();

	system.~System();

	printf("---------------------\n");

	return 0;
}