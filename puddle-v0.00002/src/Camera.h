#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <functional>

typedef std::function<void(const char*, const glm::mat4&)> updateGlobalUniformFn;

class Camera {
public:
	enum DirectionBit {
		Up = 0x001,
		Down = 0x002,
		Left = 0x04,
		Right = 0x08,
	};

	Camera(GLFWwindow* window, updateGlobalUniformFn updateGlobalUniformFn);
	~Camera();

	void move(int directionFlag, float speed, float time);

	void move(float x, float y); 

	void setPosition(glm::vec3 position);

	glm::vec3 getPosition() const;

	glm::vec3 toWorldPos(double x, double y) const;

	glm::vec4 getViewport() const;

	void updateProjection();

	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void scrollCallbackEditor(GLFWwindow* window, double xOffset, double yOffset);
	static void onWindowResize(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* m_window;

	updateGlobalUniformFn m_updateGlobalUniformFn;

	glm::vec3 m_position;

	glm::mat4 m_projection;

	float m_zoom;
};

#endif