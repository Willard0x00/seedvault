#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Editor.h"

int main() {

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1600, 900, "1.10", nullptr, nullptr);
	glfwSetWindowPos(window, 150, 100);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwSwapInterval(0);

	gl3wInit();

	Game game(window);
	game.mainLoop();

	//Editor editor(window);
	//editor.mainLoop();

	glfwDestroyWindow(window);

	glfwTerminate();
} 