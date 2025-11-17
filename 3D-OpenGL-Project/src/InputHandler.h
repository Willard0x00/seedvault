#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "SystemHandler.h"
#include "ResourceHandler.h"

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class Input {
private:
	double _mouseX;
	double _mouseY;

	System *_system;
	ResourceHandler *_resources;
public:
	int Init(System *system, ResourceHandler *resources);
	void update();

	void getMousePos() { glfwGetCursorPos(_system->_window, &_mouseX, &_mouseY); }
	void getMousePosLocked() { glfwGetCursorPos(_system->_window, &_mouseX, &_mouseY); glfwSetCursorPos(_system->_window, _system->_windowWidthHalf, _system->_windowHeightHalf); }
	bool isKey(int key) const {		return glfwGetKey(_system->_window, key);										}
	bool isExit()       const {		return (isKey(GLFW_KEY_ESCAPE) || glfwWindowShouldClose(_system->_window));		}
};

#endif