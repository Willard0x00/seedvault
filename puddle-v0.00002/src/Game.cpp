#include "Game.h"

#include <iostream>
#include <string>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

#include "Log.h"

#include "ShaderManager.h"
#include "SpriteManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"

#include "Camera.h"
#include "Map.h"
#include "Shader.h"
#include "Renderer.h"

#include "AbilityFunctions.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AbilityComponent.h"
#include "PlayerComponent.h"
#include "ItemComponent.h"

Entity* g_testEntity = nullptr;

constexpr GLfloat CLEAR_COLOR[4] = { 0, 0, 0, 0 };

constexpr float g_pi = 3.14159265;

void check_for_gl_error() {
	int r = 0;
	do {
		r = glGetError();
		if (r != 0) {
			Log::get().write(L_ERROR, "GL Error: ", r);
		}
	} while (r != 0);
}

Game::Game(GLFWwindow* window, std::string map) :
	m_window ( window ),
	m_titleUpdate ( 1000 )
{
	Log::get().write(L_SYSTEM, "Game Starting");
	glfwSwapInterval(1);

	//glfwSetWindowUserPointer(m_window, (void*)&m_camera);

	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shaderManager = std::make_unique<ShaderManager>();

	auto updateGlobalUniformMat4Bind = std::bind(&ShaderManager::updateGlobalUniformMat4, m_shaderManager.get(), std::placeholders::_1, std::placeholders::_2);
	m_camera = std::make_unique<Camera>(m_window, updateGlobalUniformMat4Bind);

	m_renderer = std::make_unique<Renderer>(m_shaderManager->getShader("rect shader"), m_shaderManager->getShader("sprite shader"), m_shaderManager->getShader("sprite batch shader"));

	auto drawRectangleBind = std::bind(&Renderer::drawRectangle, m_renderer.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	m_map = std::make_unique<Map>(10, 10, m_shaderManager->getShader("map shader"), drawRectangleBind);

	m_abilityFunctions = std::make_unique<AbilityFunctions>();

	m_spriteManager = std::make_unique<SpriteManager>();

	auto linkSpriteToComponentBind = std::bind(&SpriteManager::linkSpriteToComponent, m_spriteManager.get(), std::placeholders::_1);
	auto linkAbilityFunctionsToComponentBind = std::bind(&AbilityFunctions::linkAbiltyFunctionsToComponent, m_abilityFunctions.get(), std::placeholders::_1);
	m_entityManager = std::make_unique<EntityManager>(linkSpriteToComponentBind, linkAbilityFunctionsToComponentBind);

	if (!map.empty()) {
		map = map.substr(0, map.find_last_of('.'));
		m_map->load((map + ".kart").c_str());
		m_entityManager->load((map + ".json").c_str());
	}

	auto player = m_entityManager->getPlayer()->get<PlayerComponent>();
	auto item = m_entityManager->create(6)->get<ItemComponent>();
	player->m_inventory.add(item);
	player->m_inventory.equip(0);

	player->m_inventory.dbgPrint();
}

Game::~Game() {
	Log::get().write(L_SYSTEM, "Game Shuting Down");
}

bool Game::exitCondition() {
	return glfwWindowShouldClose(m_window) || glfwGetKey(m_window, GLFW_KEY_ESCAPE);
}

void Game::handleStuff() {
	glfwPollEvents();

	int w, h;
	glfwGetWindowSize(m_window, &w, &h);

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)) {
		double xpos, ypos;
		glfwGetCursorPos(m_window, &xpos, &ypos);

		uint8_t directionBit = 0;
		if (glfwGetKey(m_window, GLFW_KEY_W)) {
			directionBit |= 1UL << 0;
		}
		if (glfwGetKey(m_window, GLFW_KEY_S)) {
			directionBit |= 1UL << 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_A)) {
			directionBit |= 1UL << 2;
		}
		if (glfwGetKey(m_window, GLFW_KEY_D)) {
			directionBit |= 1UL << 3;
		}

		if (glfwGetKey(m_window, GLFW_KEY_E)) {
			directionBit |= 1UL << 4;
		}
		if (glfwGetKey(m_window, GLFW_KEY_Q)) {
			directionBit |= 1UL << 5;
		}

		uint8_t cameraBit = 0;
		if (glfwGetKey(m_window, GLFW_KEY_UP)) {
			cameraBit |= 1UL << 0;
		}
		if (glfwGetKey(m_window, GLFW_KEY_DOWN)) {
			cameraBit |= 1UL << 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_LEFT)) {
			cameraBit |= 1UL << 2;
		}
		if (glfwGetKey(m_window, GLFW_KEY_RIGHT)) {
			cameraBit |= 1UL << 3;
		}

		if (glfwGetKey(m_window, GLFW_KEY_Z)) {
			cameraBit |= 1UL << 4;
		}
		if (glfwGetKey(m_window, GLFW_KEY_X)) {
			cameraBit |= 1UL << 5;
		}

		auto transform = m_entityManager->getPlayer()->get<TransformComponent>();
		transform->move(directionBit, .001f);
		transform->direction(xpos / w, ypos / h);

		auto worldPos = m_camera->toWorldPos(xpos, ypos);
		m_entityManager->getPlayer()->get<PlayerComponent>()->setWeaponDirection(worldPos);
	
		m_camera->setPosition(glm::vec3(transform->m_position.x, transform->m_position.y, 0));

		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1)) {
			auto player = m_entityManager->getPlayer();
			auto newEntity = m_entityManager->create(7);
			auto ability = newEntity->get<AbilityComponent>();
			auto worldPos = m_camera->toWorldPos(xpos, ypos);

			player->get<PlayerComponent>()->attack();

			if (ability->m_onInitFn) {
				ability->m_onInitFn(this, player, newEntity, worldPos.x, worldPos.y);
			}
		}

	}

}

void Game::doStuff() {
	m_entityManager->update();
}

void Game::drawStuff() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR);

	m_map->draw();

	SpriteRenderData spriteRenderData;
	prepareSpriteRenderData(spriteRenderData);
	m_renderer->drawSpriteData(spriteRenderData);

	glfwSwapBuffers(m_window);

	check_for_gl_error();
}

void Game::analyzeStuff() {
	if (m_titleUpdate.elapsed()) {
		Log::get().write(L_INFO, "fps: ", EngineClock::get().getFramesPerSecond());
	}
}

void Game::prepareSpriteRenderData(SpriteRenderData& spriteRenderData) {
	auto& entities = m_entityManager->getEntities();

	std::vector<TransformComponent*> transforms;
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		if (auto transform = it->get<TransformComponent>()) {
			transforms.push_back(transform);
		}
	}

	spriteRenderData.send(transforms, m_camera->getViewport());
}