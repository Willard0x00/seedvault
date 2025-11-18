#include "SystemHandler.h"

System::~System() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}

int System::Init(int glversion, int samples, bool isResizable) {
	if (!glfwInit()) {
		printf("glfw failed to initialize\n");
		printf("GL_ERROR: %d\n", glGetError());
		return GLFW_ERROR;
	}

	_glversion = glversion;
	glfwWindowHint(GLFW_VERSION_MAJOR, glversion);
	glfwWindowHint(GLFW_VERSION_MINOR, glversion);
	makeWindowResizable(isResizable);
	setRenderSample(samples);

	_window = glfwCreateWindow(
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		"",
		NULL,
		NULL
	);

	glfwMakeContextCurrent(_window);
 	glfwSetWindowPos(_window, WINDOW_X, WINDOW_Y);

	_windowWidth = WINDOW_WIDTH;
	_windowWidthHalf = int(_windowWidth / 2);
	_windowHeight = WINDOW_HEIGHT;
	_windowHeightHalf = int(_windowHeight / 2);

	auto error = gl3wInit();
	if (error) {
		printf("gl3w failed to initialize\n");
		return error;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);

	_time = 0;
	_prevTime = glfwGetTime();

	_isCursorHidden = false;
	toggleCursorHidden();

	return 0;
}

void System::setRenderSample(int samples) {
	_samples = samples;
	glfwWindowHint(GLFW_SAMPLES, _samples);
}

void System::makeWindowResizable(bool isResizable) {
	_isResizable = isResizable;
	glfwWindowHint(GLFW_RESIZABLE, _isResizable);
}

void System::toggleCursorHidden() {
	if (_isCursorHidden) {
		_isCursorHidden = false;
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		_isCursorHidden = true;
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void System::update() {
	glfwSwapBuffers(_window);

	double currentTime = glfwGetTime();
	_time = currentTime - _prevTime;
	_prevTime = currentTime;
	
	if (_frameData.update()) {
		std::string title = "fms: " + std::to_string(_frameData.fms);
		glfwSetWindowTitle(_window, title.c_str());
	}
}