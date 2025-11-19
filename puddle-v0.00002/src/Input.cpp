#include "Input.h"

#include "imgui.h"

Input::Input(GLFWwindow* p_window) :
	m_window ( p_window )
{}

bool Input::getMousePressed(int button) {
	if (glfwGetMouseButton(m_window, button)) {
		if (m_heldKeys.find(button) == m_heldKeys.end()) {
			m_heldKeys.emplace(button, true);
			return true;
		}

		if (m_heldKeys.at(button)) {
			return false;
		}
		else {
			m_heldKeys.at(button) = true;
			return true;
		}
	}
	else {
		if (m_heldKeys.find(button) != m_heldKeys.end()) {
			if (m_heldKeys.at(button) == true) {
				m_releasedkeys.push_back(button);
			}
			m_heldKeys.at(button) = false;
		}
		return false;
	}
}

bool Input::getMouseHeld(int button) const {
	return glfwGetMouseButton(m_window, button);
}

bool Input::getMouseReleased(int button) const {
	for (auto key : m_releasedkeys) {
		if (key == button) {
			return true;
		}
	}
	return false;
}

void Input::clearReleased() {
	if (m_releasedkeys.size() > 0) {
		m_releasedkeys.clear();
	}
}

bool Input::notNearGui() const {
	return !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
}

bool Input::notInGui() const {
	return !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow);
}