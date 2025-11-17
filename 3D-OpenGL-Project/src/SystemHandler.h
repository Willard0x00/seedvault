#include <stdio.h>
#include <string>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#ifndef SYSTEM_HANDLER_H
#define SYSTEM_HANDLER_H

struct FrameData {
	double time = 0, prevTime = glfwGetTime(), fms = 0;
	int frames = 0;
	bool update() {
		frames++;
		if (glfwGetTime() - prevTime > 1.0) {
			fms = 1000.0 / double(frames);
			frames = 0;
			prevTime += 1.0;
			return true;
		}
		return false;
	}
};

class System {
private:
	enum {
		GLFW_ERROR = -1,
		GLEW_ERROR = -2,
		WINDOW_WIDTH = 1100,
		WINDOW_HEIGHT = 800,
		WINDOW_X = 500,
		WINDOW_Y = 200
	};

	int _glversion;
	int _samples;
	int _windowWidth, _windowWidthHalf;
	int _windowHeight, _windowHeightHalf;
	double _time, _prevTime;

	bool _isResizable;
	bool _isCursorHidden;

	GLFWwindow *_window;

	FrameData _frameData;

	friend class Input;
public:
	~System();
	int Init(int glversion, int samples, bool isResizable);
	void setRenderSample(int samples);
	void makeWindowResizable(bool isResizable);
	void toggleCursorHidden();
	void update();

	int getWindowWidthHalf()  { return _windowWidthHalf;  }
	int getWindowHeightHalf() { return _windowHeightHalf; }
	double getTime()		  { return _time;			  }
};

#endif