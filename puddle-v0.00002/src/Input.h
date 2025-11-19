#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <map>
#include <vector>

class Input {
public:
	Input(GLFWwindow* p_window);

	bool getMousePressed(int button);

	bool getMouseHeld(int button) const;

	bool getMouseReleased(int button) const;

	bool notNearGui() const;

	bool notInGui() const;

	void clearReleased();
private:
	GLFWwindow* m_window;

	std::map<int, bool> m_heldKeys;
	std::vector<int> m_releasedkeys;
};

#endif