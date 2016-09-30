#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include "Window.h"

#include "GameController.h"
// Input manager stores a key map that maps SDL_Keys to booleans.
// If the value in the key map is true, then the key is pressed.
// Otherwise, it is released.
class InputManager {
public:

	static InputManager& Instance() {
		static InputManager instance;
		return instance;
	}

	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	void init();
	void clean();

	void handleInput();
	
		//Returns true if the key was just pressed
	bool isKeyPressed(unsigned int keyID); 
	unsigned int keyPressed();
		
		//Returns true if the key is held down
	bool isKeyDown(unsigned int keyID);
	unsigned int keyDown();
	int getAxis();

	glm::ivec2 getMouseCoords() { return _mouseCoords; }

private:

	InputManager() {}

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	void setMouseCoords(int x, int y);
	bool wasKeyDown(unsigned int keyID);
	std::unordered_map<unsigned int, bool> _previousKeyMap;
	std::unordered_map<unsigned int, bool> _keyMap;
	glm::ivec2 _mouseCoords;

	SDL_Joystick* gameController;
};
