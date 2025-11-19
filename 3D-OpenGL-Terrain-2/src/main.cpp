#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Clock.h"
#include "Window.h"
#include "Camera.h"
#include "Scene.h"
#include "Terrain.h"
#include "TerrainLoader.h"
#include "TerrainBrush.h"
#include "Timer.h"

constexpr GLfloat CLEAR_COLOR[4] = { 0, 0, 0, 0 };

int main() {
	Clock clock;

	glfwInit();

	Window window;

	gl3wInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	Camera camera(&window, Camera::Settings());

	Scene scene;
	scene.load_assimp("Data/Models/Box/", "box.obj");
	scene.set_transform(Transform(glm::vec3(0, 0, 0)));

	Program program;
	program.load("Data/Shaders/basic shader.glsl");

	scene.attach_program(&program);
	camera.attach_program(&program);

	Program terrain_program;
	terrain_program.load("Data/Shaders/terrain shader.glsl");

	Terrain terrain(5, &terrain_program);
	camera.attach_program(&terrain_program);

	Program brush_program;
	brush_program.load("Data/Shaders/terrain brush.glsl");
	camera.attach_program(&brush_program);

	TerrainBrush brush(&brush_program);

	auto position = camera.get_position();
	terrain.start_chunk_loader(&position->x, &position->z);

	std::cout << "-------------MAIN LOOP------------------\n";
	while (!glfwWindowShouldClose(window.get()) && !glfwGetKey(window.get(), GLFW_KEY_ESCAPE)) {
		camera.update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR);

		//scene.draw();

		terrain.draw();
		brush.draw();

		glfwSwapBuffers(window.get());

		int r = 0;
		do {
			r = glGetError();
			if (r != 0)
				std::cout << "GLError -> " << r << '\n';
		} while (r != 0);

		static Timer timer(1);
		if(timer.update()) {
			std::string title = "fps: " + std::to_string(clock.get_fps()) + " fms: " + std::to_string(clock.get_frame_time_ms());
			window.set_title(title);
		}

		clock.update();

		brush.update(camera.mouse_to_3d_vector(), *camera.get_position());

		glfwPollEvents();

		if (glfwGetWindowAttrib(window.get(), GLFW_FOCUSED)) {
			double xpos, ypos;
			glfwGetCursorPos(window.get(), &xpos, &ypos);
			camera.move_angle((float)xpos, (float)ypos);

			if (glfwGetKey(window.get(), GLFW_KEY_W)) {
				camera.move(CAMERA_FORWARD, clock.get_frame_time_ms());
			}
			if (glfwGetKey(window.get(), GLFW_KEY_S)) {
				camera.move(CAMERA_BACKWARD, clock.get_frame_time_ms());
			}
			if (glfwGetKey(window.get(), GLFW_KEY_A)) {
				camera.move(CAMERA_LEFT, clock.get_frame_time_ms());
			}
			if (glfwGetKey(window.get(), GLFW_KEY_D)) {
				camera.move(CAMERA_RIGHT, clock.get_frame_time_ms());
			}
			if (glfwGetKey(window.get(), GLFW_KEY_Q)) {
				camera.move(CAMERA_DOWN, clock.get_frame_time_ms());
			}
			if (glfwGetKey(window.get(), GLFW_KEY_E)) {
				camera.move(CAMERA_UP, clock.get_frame_time_ms());
			}

			if(glfwGetMouseButton(window.get(), GLFW_MOUSE_BUTTON_1)) {
				brush.raise(terrain.get_chunks());
			}
		}

	}

	return 0;
}