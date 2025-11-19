#include "Camera.h"

#include "Log.h"

#include <imgui.h>

constexpr float g_zNear = 0.0f;
constexpr float g_zFar = 1.0f;

Camera::Camera(GLFWwindow* window, updateGlobalUniformFn updateGlobalUniformFn) :
	m_window ( window ),
	m_updateGlobalUniformFn ( updateGlobalUniformFn ),
	m_position ( 0, 0, 0 ),
	m_zoom ( .2f )
{
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	glViewport(0, 0, w, h);
	glScissor(0, 0, w, h);
	m_projection = glm::ortho(0.0f, (float)w, (float)h, 0.0f, g_zNear, g_zFar);

	m_updateGlobalUniformFn("projection", m_projection);

	glfwSetWindowUserPointer(m_window, this);
	glfwSetScrollCallback(m_window, Camera::scrollCallback);
	glfwSetWindowSizeCallback(m_window, Camera::onWindowResize);
}

Camera::~Camera() {

}

void Camera::move(int directionFlag, float speed, float time) {
	const bool y = directionFlag & DirectionBit::Up || directionFlag & DirectionBit::Down;
	const bool x = directionFlag & DirectionBit::Left || directionFlag & DirectionBit::Right;

	const float distance = speed * time;

	glm::vec3 vector = glm::normalize(glm::vec3((x) ? 1.0f : 0.0f, (y) ? 1.0f : 0.0f, 0.0f)) * distance;
	if (directionFlag & DirectionBit::Left) {
		m_position.x -= vector.x;
	}
	if (directionFlag & DirectionBit::Right) {
		m_position.x += vector.x;
	}
	if (directionFlag & DirectionBit::Up) {
		m_position.y -= vector.y;
	}
	if (directionFlag & DirectionBit::Down) {
		m_position.y += vector.y;
	}

	updateProjection();

	//Log::get().write(L_DEBUG, m_position.x, " ", m_position.y, " ", m_position.z);
}

void Camera::move(float x, float y) {
	m_position.x -= x;
	m_position.y -= y;

	updateProjection();
}

void Camera::setPosition(glm::vec3 position) {
	m_position = position;

	updateProjection();
}

glm::vec3 Camera::getPosition() const {
	return m_position;
}

glm::vec3 Camera::toWorldPos(double x, double y) const {
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	x /= w;
	y /= h;
	x -= 0.5;
	y -= 0.5;

	float aspectRatio = (float)w / (float)h;

	float xoffset = m_position.x / (aspectRatio * w * m_zoom);
	float yoffset = m_position.y / (aspectRatio * h * m_zoom);

	return glm::vec3(
		(x + xoffset) * (aspectRatio * w * m_zoom),
		(y + yoffset) * (aspectRatio * h * m_zoom),
		0
	);
}

void Camera::updateProjection() {
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);

	float aspectRatio = (float)w / (float)h;

	m_projection = glm::ortho(
		(-aspectRatio * w / 2) * m_zoom + m_position.x,
		(aspectRatio * w / 2) * m_zoom + m_position.x,
		(aspectRatio * h / 2) * m_zoom + m_position.y,
		(-aspectRatio * h / 2) * m_zoom + m_position.y,
		g_zNear,
		g_zFar
	);

	m_updateGlobalUniformFn("projection", m_projection);
}

void Camera::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	auto camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

	camera->m_zoom -= yOffset * 0.010f;

	camera->updateProjection();
}

void Camera::scrollCallbackEditor(GLFWwindow* window, double xOffset, double yOffset) {
	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
		auto camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

		camera->m_zoom -= yOffset * 0.010f;

		camera->updateProjection();
	}
}

void Camera::onWindowResize(GLFWwindow* window, int width, int height) {
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);

	camera->updateProjection();
}

glm::vec4 Camera::getViewport() const {
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);

	float scale = m_zoom / 0.5f;
	float width = w * scale;
	float height = h * scale;
	return glm::vec4(m_position.x - width * 0.5f, m_position.y - height * 0.5f, width, height);
}