#include "Game.h"

#include <iostream>

#include "Sprite.h"

#include "SpriteComponent.h"
#include "TransformComponent.h"

constexpr GLfloat CLEAR_COLOR[4] = { 0, 0, 0, 0 };

void check_for_gl_error() {
	int r = 0;
	do {
		r = glGetError();
		if (r != 0) {
			std::cout << "GL Error: " << r << '\n';
		}
	} while (r != 0);
}

Game::Game(GLFWwindow* window) :
	m_window ( window ),
	m_camera ( window, CameraSettings() )
{
	glfwSwapInterval(1);
	glfwSetWindowSizeCallback(m_window, Camera::onWindowResize);
	glfwSetWindowUserPointer(m_window, (void*)&m_camera);

	m_programManager.attach_camera(&m_camera);
	m_player = m_entityManager.create(0);
}

Game::~Game() {}

bool Game::exitCondition() {
	return glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE);
}

void Game::handleStuff() {
	m_lastFrame = std::chrono::system_clock::now();

	glfwPollEvents();

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)) {

		uint8_t op = 0;
		if (glfwGetKey(m_window, GLFW_KEY_W)) {
			op |= 1UL << 0;
		}
		if (glfwGetKey(m_window, GLFW_KEY_S)) {
			op |= 1UL << 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_A)) {
			op |= 1UL << 2;
		}
		if (glfwGetKey(m_window, GLFW_KEY_D)) {
			op |= 1UL << 3;
		}

		if (glfwGetKey(m_window, GLFW_KEY_Q)) {
			op |= 1UL << 4;
		}
		if (glfwGetKey(m_window, GLFW_KEY_E)) {
			op |= 1UL << 5;
		}

		auto transform = m_player->get<TransformComponent>();
		//transform->move(op, (std::chrono::system_clock::now() - m_lastFrame).count() / 1000.0f);
		transform->move(op);

		if (glfwGetKey(m_window, GLFW_KEY_Z)) {
			transform->_scale.x -= 1;
			transform->_scale.y -= 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_C)) {
			transform->_scale.x += 1;
			transform->_scale.y += 1;
		}
	}
}

void Game::doStuff() {
	m_entityManager.update();
}

void Game::drawStuff() {
	m_map.draw(m_programManager.get(1), GL_TRIANGLES);

	auto entities = m_entityManager.getEntities();
	for (auto it = entities->begin(); it != entities->end(); ++it) {
		if (auto spriteComponent = it->get<SpriteComponent>()) {
			auto transformComponent = it->get<TransformComponent>();
			auto sprite = m_spriteManager.get(spriteComponent->_id);
			auto shader = m_programManager.get(spriteComponent->_shader);
			sprite->draw(shader, GL_TRIANGLES, transformComponent, spriteComponent);
		}
	}

	glfwSwapBuffers(m_window);

	check_for_gl_error();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR);
}