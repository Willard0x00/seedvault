#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

#include "Engine.h"

int main() {

	HWND console = GetConsoleWindow();
	SetWindowPos(console, NULL, -1000, 100, 1000, 500, NULL);

	auto result = glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

	if (!result) {
		return -1;
	}

	Engine engine;
	engine.run();

	return 0;
}