#include "Editor.h"

#include <iostream>

#include <GL/gl3w.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

Editor::Editor(GLFWwindow* window) :
	m_window	 ( window ),
	m_camera	 ( window, CameraSettings()),
	m_menuUI	 ( std::bind(&Map::save, &m_map, std::placeholders::_1) )
{
	m_programManager.attach_camera(&m_camera);

	glfwSetWindowSizeCallback(m_window, Camera::onWindowResize);
	glfwSetWindowUserPointer(m_window, (void*)&m_camera);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	ImGui::StyleColorsDark();

	m_map.load("Data/Maps/default.kart");
}

Editor::~Editor() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

constexpr GLfloat CLEAR_COLOR[4] = { 0, 0, .2f, 0 };

void check_for_gl_error_editor() {
	int r = 0;
	do {
		r = glGetError();
		if (r != 0) {
			std::cout << "GL Error: " << r << '\n';
		}
	} while (r != 0);
}

bool Editor::exitCondition() {
	return glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE);
}

void Editor::handleStuff() {
	glfwPollEvents();

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)) {
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);

		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1)) {
			int w, h;
			glfwGetWindowSize(m_window, &w, &h);

			if (x >= 0 && x < w && y >= 0 && y < h) {
				m_map.setTile(x, y, m_tileUI.m_selected);
			}
		}
	}
}

void Editor::doStuff() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Editor::drawStuff() {
	auto mapShader = m_programManager.get(1);
	m_map.draw(mapShader, GL_TRIANGLES);

	m_menuUI.draw();
	m_tileUI.draw();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_window);

	check_for_gl_error_editor();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR);
}

void Editor::onWindowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
}