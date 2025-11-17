#include "InputHandler.h"

int Input::Init(System *system, ResourceHandler *resources) {
	_system = system;
	_resources = resources;
	return 0;
}

void Input::update() {
	glfwPollEvents();
	getMousePosLocked();
	_resources->updateCameraAngles(
		_system->getTime(),
		_system->getWindowWidthHalf(),
		_system->getWindowHeightHalf(),
		_mouseX,
		_mouseY
	);

	if (isKey(GLFW_KEY_W)) {
		_resources->updateCameraUp(_system->getTime());
	}
	if (isKey(GLFW_KEY_S)) {
		_resources->updateCameraDown(_system->getTime());
	}
	if (isKey(GLFW_KEY_D)) {
		_resources->updateCameraRight(_system->getTime());
	}
	if (isKey(GLFW_KEY_A)) {
		_resources->updateCameraLeft(_system->getTime());
	}
	if (isKey(GLFW_KEY_Z)) {
		_resources->updateObjectUp(_system->getTime(), 0);
	}
	if (isKey(GLFW_KEY_X)) {
		_resources->updateObjectDown(_system->getTime(), 0);
	}
	if (isKey(GLFW_KEY_C)) {
		_resources->updateObjectLeft(_system->getTime(), 0);
	}
	if (isKey(GLFW_KEY_V)) {
		_resources->updateObjectRight(_system->getTime(), 0);
	}
	if (isKey(GLFW_KEY_B)) {
		_resources->updateObjectScale(1.001f, 0);
	}
	if (isKey(GLFW_KEY_N)) {
		_resources->updateObjectScale(.999f, 0);
	}
}