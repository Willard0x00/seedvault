#include "Editor.h"

#include <iostream>
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Log.h"

#include "ShaderManager.h"
#include "SpriteManager.h"
#include "EntityManager.h"

#include "Input.h"
#include "Camera.h"
#include "Map.h"
#include "Shader.h"
#include "Renderer.h"

#include "AbilityFunctions.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AbilityComponent.h"

#include "StyleGui.hpp"
#include "TileGui.h"
#include "MenuGui.h"
#include "ObjectGui.h"
#include "EnemyGui.h"
#include "ItemGui.h"
#include "SelectionGui.h"
#include "EntityTreeGui.h"

constexpr GLfloat CLEAR_COLOR[4] = { 0, 0, 0, 0 };

void check_for_gl_error_editor() {
	int r = 0;
	do {
		r = glGetError();
		if (r != 0) {
			Log::get().write(L_ERROR, "GL Error: ", r);
		}
	} while (r != 0);
}

Editor::Editor(GLFWwindow* window, std::string map) :
	m_window(window),
	m_titleUpdate(1000)
{
	Log::get().write(L_SYSTEM, "Editor Starting");
	glfwSwapInterval(1);

	//glfwSetWindowSizeCallback(m_window, Camera::onWindowResize);
	//glfwSetWindowUserPointer(m_window, (void*)&m_camera);

	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shaderManager = std::make_unique<ShaderManager>();

	m_input = std::make_unique<Input>(m_window);

	auto updateGlobalUniformMat4Bind = std::bind(&ShaderManager::updateGlobalUniformMat4, m_shaderManager.get(), std::placeholders::_1, std::placeholders::_2);
	m_camera = std::make_unique<Camera>(m_window, updateGlobalUniformMat4Bind);

	// override scrollcallback
	glfwSetScrollCallback(m_window, Camera::scrollCallbackEditor);

	m_renderer = std::make_unique<Renderer>(m_shaderManager->getShader("rect shader"), m_shaderManager->getShader("sprite shader"), m_shaderManager->getShader("sprite batch shader"));

	auto drawRectangleBind = std::bind(&Renderer::drawRectangle, m_renderer.get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	m_map = std::make_unique<Map>(10, 10, m_shaderManager->getShader("map shader"), drawRectangleBind);

	m_abilityFunctions = std::make_unique<AbilityFunctions>();

	m_spriteManager = std::make_unique<SpriteManager>();

	auto linkSpriteToComponentBind = std::bind(&SpriteManager::linkSpriteToComponent, m_spriteManager.get(), std::placeholders::_1);
	auto linkAbilityFunctionsToComponentBind = std::bind(&AbilityFunctions::linkAbiltyFunctionsToComponent, m_abilityFunctions.get(), std::placeholders::_1);
	m_entityManager = std::make_unique<EntityManager>(linkSpriteToComponentBind, linkAbilityFunctionsToComponentBind);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	setStyle(ImGui::GetStyle());

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	m_tileGui = std::make_unique<TileGui>(m_selection);

	auto newMapBind = std::bind(&Map::create, m_map.get(), std::placeholders::_1);
	auto saveMapBind = std::bind(&Map::save, m_map.get(), std::placeholders::_1);
	auto loadMapBind = std::bind(&Map::load, m_map.get(), std::placeholders::_1);
	auto saveEntitiesBind = std::bind(&EntityManager::save, m_entityManager.get(), std::placeholders::_1);
	auto loadEntitiesBind = std::bind(&EntityManager::load, m_entityManager.get(), std::placeholders::_1);
	m_menuGui = std::make_unique<MenuGui>(newMapBind, saveMapBind, loadMapBind, saveEntitiesBind, loadEntitiesBind, m_map->getMapName());
	m_objectGui = std::make_unique<ObjectGui>(m_selection, m_entityManager->getEntityCache());
	m_enemyGui = std::make_unique<EnemyGui>(m_selection, m_entityManager->getEntityCache());
	m_itemGui = std::make_unique<ItemGui>(m_selection, m_entityManager->getEntityCache());
	m_selectionGui = std::make_unique<SelectionGui>(m_selection, true, false);

	auto removeEntityBind = std::bind(&EntityManager::remove, m_entityManager.get(), std::placeholders::_1);
	auto duplicateEntityBind = std::bind(&EntityManager::duplicate, m_entityManager.get(), std::placeholders::_1);
	m_entityTreeGui = std::make_unique<EntityTreeGui>(m_selection, removeEntityBind, duplicateEntityBind);

	if (!map.empty()) {
		map = map.substr(0, map.find_last_of('.'));
		m_map->load((map + ".kart").c_str());
		m_entityManager->load((map + ".json").c_str());
	}
}

Editor::~Editor() {
	Log::get().write(L_SYSTEM, "Editor Shuting Down");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool Editor::exitCondition() {
	return glfwWindowShouldClose(m_window);
}

void Editor::handleStuff() {
	glfwPollEvents();

	int w, h;
	glfwGetWindowSize(m_window, &w, &h);

	if (glfwGetWindowAttrib(m_window, GLFW_FOCUSED)) {
		double xpos, ypos;
		glfwGetCursorPos(m_window, &xpos, &ypos);

		uint8_t cameraBit = 0;
		if (glfwGetKey(m_window, GLFW_KEY_W) && m_input->notInGui()) {
			cameraBit |= 1UL << 0;
		}
		if (glfwGetKey(m_window, GLFW_KEY_S) && m_input->notInGui()) {
			cameraBit |= 1UL << 1;
		}
		if (glfwGetKey(m_window, GLFW_KEY_A) && m_input->notInGui()) {
			cameraBit |= 1UL << 2;
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) && m_input->notInGui()) {
			cameraBit |= 1UL << 3;
		}

		m_camera->move(cameraBit, 4000, .001f);

		if (m_input->getMousePressed(GLFW_MOUSE_BUTTON_3)) {
			m_cameraDrag = glm::vec4(xpos, ypos, 0, 0);
		}
		if (m_input->getMouseHeld(GLFW_MOUSE_BUTTON_3)) {
			m_cameraDrag.z = (float)xpos - m_cameraDrag.x;
			m_cameraDrag.w = (float)ypos - m_cameraDrag.y;

			m_camera->move(m_cameraDrag.z / (float)w * 700.0f, m_cameraDrag.w / (float)h * 700.0f);
			m_cameraDrag.x += m_cameraDrag.z;
			m_cameraDrag.y += m_cameraDrag.w;
		}

		if (m_input->getMousePressed(GLFW_MOUSE_BUTTON_2)) {
			m_selection.clear();
			m_selection.clearGrab();
		}

		auto worldPos = m_camera->toWorldPos(xpos, ypos); 

		switch (m_selection.m_type) {
		case SelectionType::NONE:	selectNone(worldPos);	break;
		case SelectionType::TILE:	selectTile(worldPos);	break;
		case SelectionType::Object:	selectObject(worldPos);	break;
		case SelectionType::Enemy:	selectEnemy(worldPos);	break;
		case SelectionType::Item:   selectItem(worldPos);   break;
		default:	break;
		};
	}

	m_input->clearReleased();
}

void Editor::doStuff() {
	m_entityManager->update();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + ImGui::GetFrameHeight()));
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
	ImGuiID dockSpaceID = ImGui::GetID("InvisibleWindowDockSpace");
	ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
	ImGui::End();
}

void Editor::drawStuff() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearBufferfv(GL_COLOR, 0, CLEAR_COLOR);

	m_map->draw(true);

	SpriteRenderData spriteRenderData;
	prepareSpriteRenderData(spriteRenderData);
	m_renderer->drawSpriteData(spriteRenderData);

	m_tileGui->draw();
	m_objectGui->draw();
	m_enemyGui->draw();
	m_itemGui->draw();
	m_selectionGui->draw();
	m_entityTreeGui->draw();

	switch (m_selection.m_type) {
	case SelectionType::NONE:	drawNoneSelection();	break;
	case SelectionType::TILE:	m_map->drawMarker();	break;
	case SelectionType::Object: drawObjectSelection();	break;
	case SelectionType::Enemy:	drawEnemySelection();	break;
	case SelectionType::Item:   drawItemSelection();    break;
	default:											break;
	};

	m_menuGui->draw();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupCurrentContext);
	}

	glfwSwapBuffers(m_window);

	check_for_gl_error_editor();
}

void Editor::analyzeStuff() {
	if (m_titleUpdate.elapsed()) {
		//Log::get().write(L_INFO, "fps: ", EngineClock::get().getFramesPerSecond());
	}
}

void Editor::selectNone(glm::vec3 worldPos) {
	bool mouseButton1Pressed = m_input->getMousePressed(GLFW_MOUSE_BUTTON_1);
	if (mouseButton1Pressed && m_input->notNearGui() && !glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT)) {
		m_selection.clearGrab();
		m_selection.m_cursorGrab = glm::vec4(worldPos.x, worldPos.y, 0, 0);
		m_selection.m_isGrabbing = true;
	}
	else if (mouseButton1Pressed && m_input->notNearGui() && glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT)) {
		m_selection.clearGrab();
		glm::vec4 rect = glm::vec4(worldPos.x, worldPos.y, 0, 0);
		auto& entities = m_entityManager->getEntities();
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			if (auto transform = it->get<TransformComponent>()) {
				if (transform->collidesWith(rect, true)) {
					m_selection.m_entities.push_back((*it));
					if (auto sprite = it->get<SpriteComponent>()) {
						sprite->m_highlight = true;
					}
					break;
				}
			}
		}
	}
	if (m_input->getMouseHeld(GLFW_MOUSE_BUTTON_1) && !glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT)) {
		m_selection.m_cursorGrab.z = worldPos.x - m_selection.m_cursorGrab.x;
		m_selection.m_cursorGrab.w = worldPos.y - m_selection.m_cursorGrab.y;

	}
	else if (m_input->getMouseHeld(GLFW_MOUSE_BUTTON_1) && glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT)) {
		if (m_selection.m_entities.size() > 0) {
			if (auto transform = m_selection.m_entities[0]->get<TransformComponent>()) {
				transform->m_position = glm::vec3(worldPos.x, worldPos.y, 0);
			}
		}
	}
	else if (m_input->getMouseReleased(GLFW_MOUSE_BUTTON_1) && !glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT)) {
		if (m_selection.m_isGrabbing) {
			m_selection.m_isGrabbing = false;
			glm::vec4 rect;
			if (m_selection.hasGrab()) {
				rect = m_selection.m_cursorGrab;
				if (rect.z < 0) {
					rect.x = rect.x + rect.z;
					rect.z = abs(rect.z);
				}
				if (rect.w < 0) {
					rect.y = rect.y + rect.w;
					rect.w = abs(rect.w);
				}
				auto& entities = m_entityManager->getEntities();
				for (auto it = entities.begin(); it != entities.end(); ++it) {
					if (auto transform = it->get<TransformComponent>()) {
						if (transform->collidesWith(rect, false)) {
							m_selection.m_entities.push_back((*it));
							if (auto sprite = it->get<SpriteComponent>()) {
								sprite->m_highlight = true;
							}
						}
					}
				}
				m_selection.m_cursorGrab = glm::vec4(0, 0, 0, 0);
			}
			else {
				rect = glm::vec4(worldPos.x, worldPos.y, 0, 0);
				auto& entities = m_entityManager->getEntities();
				for (auto it = entities.begin(); it != entities.end(); ++it) {
					if (auto transform = it->get<TransformComponent>()) {
						if (transform->collidesWith(rect, true)) {
							m_selection.m_entities.push_back((*it));
							if (auto sprite = it->get<SpriteComponent>()) {
								sprite->m_highlight = true;
							}
							break;
						}
					}
				}
			}
		}
	}
}

void Editor::selectTile(glm::vec3 worldPos) {
	m_map->setMarker(worldPos.x, worldPos.y, MarkerFlag::CENTER);

	if (m_input->getMouseHeld(GLFW_MOUSE_BUTTON_1) && m_input->notNearGui()) {
		m_map->setTile(worldPos.x, worldPos.y, m_selection.m_id);
	}
}

void Editor::selectObject(glm::vec3 worldPos) {
	m_map->setMarker(worldPos.x, worldPos.y, m_selectionGui->m_center ? MarkerFlag::CENTER : MarkerFlag::CORNER);
	m_objectGui->setCursor(worldPos.x, worldPos.y);

	if (m_input->getMousePressed(GLFW_MOUSE_BUTTON_1) && m_input->notNearGui()) {
		auto entity = m_entityManager->create(m_selection.m_id);
		glm::vec2 position;
		if (m_selectionGui->m_center) {
			position = m_map->center(worldPos.x, worldPos.y);
		}
		else if (m_selectionGui->m_corner) {
			position = m_map->corner(worldPos.x, worldPos.y);
		}
		else {
			position = glm::vec3(worldPos.x, worldPos.y, 0);
		}
		entity->get<TransformComponent>()->m_position = glm::vec3(position, 0);
	}
}

void Editor::selectEnemy(glm::vec3 worldPos) {
	m_map->setMarker(worldPos.x, worldPos.y, m_selectionGui->m_center ? MarkerFlag::CENTER : MarkerFlag::CORNER);
	m_enemyGui->setCursor(worldPos.x, worldPos.y);

	if (m_input->getMousePressed(GLFW_MOUSE_BUTTON_1) && m_input->notNearGui()) {
		auto entity = m_entityManager->create(m_selection.m_id);
		glm::vec2 position;
		if (m_selectionGui->m_center) {
			position = m_map->center(worldPos.x, worldPos.y);
		}
		else if (m_selectionGui->m_corner) {
			position = m_map->corner(worldPos.x, worldPos.y);
		}
		else {
			position = glm::vec3(worldPos.x, worldPos.y, 0);
		}
		entity->get<TransformComponent>()->m_position = glm::vec3(position, 0);
	}
}

void Editor::selectItem(glm::vec3 worldPos) {
	m_map->setMarker(worldPos.x, worldPos.y, m_selectionGui->m_center ? MarkerFlag::CENTER : MarkerFlag::CORNER);
	m_itemGui->setCursor(worldPos.x, worldPos.y);

	if (m_input->getMousePressed(GLFW_MOUSE_BUTTON_1) && m_input->notNearGui()) {
		auto entity = m_entityManager->create(m_selection.m_id);
		glm::vec2 position;
		if (m_selectionGui->m_center) {
			position = m_map->center(worldPos.x, worldPos.y);
		}
		else if (m_selectionGui->m_corner) {
			position = m_map->corner(worldPos.x, worldPos.y);
		}
		else {
			position = glm::vec3(worldPos.x, worldPos.y, 0);
		}
		entity->get<TransformComponent>()->m_position = glm::vec3(position, 0);
	}
}

void Editor::drawNoneSelection() {
	if (m_selection.m_isGrabbing) {
		m_renderer->drawRectangle(m_selection.m_cursorGrab, glm::vec4(0.4, 0.4, 0.7, 0.4), RendererFlag::drawRectNonCenter);
	}
}

void Editor::drawObjectSelection() {
	m_map->drawMarker();
	auto objectCursor = m_objectGui->getCursor();
	m_renderer->drawSprite(objectCursor.transform.getModel(), objectCursor.sprite);
}

void Editor::drawEnemySelection() {
	m_map->drawMarker();
	auto enemyCursor = m_enemyGui->getCursor();
	m_renderer->drawSprite(enemyCursor.transform.getModel(), enemyCursor.sprite);
}

void Editor::drawItemSelection() {
	m_map->drawMarker();
	auto itemCursor = m_itemGui->getCursor();
	m_renderer->drawSprite(itemCursor.transform.getModel(), itemCursor.sprite);
}

void Editor::prepareSpriteRenderData(SpriteRenderData& spriteRenderData) {
	auto& entities = m_entityManager->getEntities();

	std::vector<TransformComponent*> transforms;
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		if (auto transform = it->get<TransformComponent>()) {
			transforms.push_back(transform);
		}
	}

	spriteRenderData.send(transforms, m_camera->getViewport());
}