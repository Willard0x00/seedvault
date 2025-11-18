#include <SDL3/SDL.h>
#include <map>

#ifndef INPUT_H
#define INPUT_H


class Input {
private:
	const bool* _keys;
	std::map<SDL_Keycode, bool> _keymap;
	std::map<unsigned int, bool> _mousemap;
public:
	//Update the state of the input devices
	//and checks if the window has been closed
	bool get(SDL_Window* window);
	//Check if a key is pressed
	bool isKey(const SDL_Keycode& key);
	//Check if a key is held down
	bool isHeld(const SDL_Keycode& key);
	//Check if a mouse button is pressed
	//button == SDL_BUTTON
	bool isMouse(float& nx, float& ny, const unsigned int& button, SDL_Window* window);
	//Check if a mouse button is held
	//button == SDL_BUTTON
	bool isMouseHeld(float& nx, float& ny, const unsigned int& button, SDL_Window* window);
};

#endif