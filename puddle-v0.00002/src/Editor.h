#ifndef EDITOR_H
#define EDITOR_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>

#include "Engine.h"
#include "Selection.h"
#include "SpriteRenderData.h"

class Input;
class Camera;
class Map;
class ShaderManager;
class EntityManager;
class SpriteManager;
class Renderer;

class AbilityFunctions;

struct TileGui;
struct MenuGui;
struct ObjectGui;
struct EnemyGui;
struct ItemGui;
struct SelectionGui;
struct EntityTreeGui;

class Editor : public Engine {
public:
	Editor(GLFWwindow* window, std::string map);
	~Editor();

	bool exitCondition();

	void handleStuff();

	void doStuff();

	void drawStuff();

	void analyzeStuff();

	void selectNone(glm::vec3 worldPos);

	void selectTile(glm::vec3 worldPos);

	void selectObject(glm::vec3 worldPos);

	void selectEnemy(glm::vec3 worldPos);

	void selectItem(glm::vec3 worldPos);

	void drawNoneSelection();

	void drawObjectSelection();

	void drawEnemySelection();

	void drawItemSelection();

	void prepareSpriteRenderData(SpriteRenderData& spriteRenderData);
private:
	GLFWwindow* m_window;

	Timer m_titleUpdate;

	std::unique_ptr<Input> m_input;

	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<Map> m_map;

	std::unique_ptr<AbilityFunctions> m_abilityFunctions;

	std::unique_ptr<ShaderManager> m_shaderManager;

	std::unique_ptr<SpriteManager> m_spriteManager;

	std::unique_ptr<EntityManager> m_entityManager;

	std::unique_ptr<Renderer> m_renderer;

	std::unique_ptr<TileGui> m_tileGui;

	std::unique_ptr<MenuGui> m_menuGui;

	std::unique_ptr<ObjectGui> m_objectGui;

	std::unique_ptr<EnemyGui> m_enemyGui;

	std::unique_ptr<ItemGui> m_itemGui;

	std::unique_ptr<SelectionGui> m_selectionGui;

	std::unique_ptr<EntityTreeGui> m_entityTreeGui;

	Selection m_selection;

	glm::vec4 m_cameraDrag;
};

#endif