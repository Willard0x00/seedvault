#ifndef GAME_H
#define GAME_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>

#include "Engine.h"

#include "SpriteRenderData.h"

class Camera;
class Map;
class ShaderManager;
class EntityManager;
class SpriteManager;
class Renderer;
class AbilityFunctions;

class Game : public Engine {
public:
	Game(GLFWwindow* window, std::string map);
	~Game();

	bool exitCondition();

	void handleStuff();

	void doStuff();

	void drawStuff();

	void analyzeStuff();

	void prepareSpriteRenderData(SpriteRenderData& spriteRenderData);
private:
	GLFWwindow* m_window;

	Timer m_titleUpdate;

	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<Map> m_map;

	std::unique_ptr<AbilityFunctions> m_abilityFunctions;

	std::unique_ptr<ShaderManager> m_shaderManager;

	std::unique_ptr<SpriteManager> m_spriteManager;

	std::unique_ptr<EntityManager> m_entityManager;

	std::unique_ptr<Renderer> m_renderer;
};

#endif