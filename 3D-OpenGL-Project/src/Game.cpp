#include "Game.h"

int Game::Init(
	System *system,
	Input *input,
	ResourceHandler *resources,
	Renderer *renderer
) {
	_system = system;
	_input = input;
	_resources = resources;
	_renderer = renderer;

	return 0;
}

void Game::begin() {

	while (!_input->isExit()) {
		update();
		input();
		display();
	}
}

void Game::input() {
	_input->update();
}

void Game::update() {
	_resources->updateObjects();

	_resources->updateObjectUp(_system->getTime(), 1);

	_resources->updateCamera();
}

void Game::display() {
	_renderer->clear();
	_renderer->renderObjects();
	_system->update();
}