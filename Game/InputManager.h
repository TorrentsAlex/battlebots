#pragma once
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include "Window.h"

#include "TurriFramework.h"

#include "Command.h"
#include "ButtonCommands.h"
#include "AxisCommand.h"
#include "GamePad.h"

// Input manager stores a key map that maps SDL_Keys to booleans.
// If the value in the key map is true, then the key is pressed.
// Otherwise, it is released.

const int JOYSTICK_DEAD_ZONE = 8000;
struct GamePadButtonState;
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
	void handleInput(GamePad& pad);
	
	//Returns true if the key was just pressed
	bool isKeyPressed(unsigned int keyID); 
	unsigned int keyPressed();
	bool isKeyPressed(GamePadButtonState keyID);

	// Game Pad buttons
	std::vector<Command*> getGamePadCommand(GamePad& pad);
	std::vector<JoystickCommand*> getGamePadJoysticks(GamePad& pad);

	void getGameController(GamePad& gamePad);
	void closeController(GamePad& pad);
	void mapping(GamePad& pad);

		//Returns true if the key is held down
	bool isKeyDown(unsigned int keyID);
	unsigned int keyDown();
	int getAxis();

	glm::ivec2 getMouseCoords() { return _mouseCoords; }

private:
	int numControllers;
	InputManager() {}

	std::unordered_map<unsigned int, bool> _previousKeyMap;
	std::unordered_map<unsigned int, bool> _keyMap;

	glm::ivec2 _mouseCoords;
	
	// gestionate keyboard inputs
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	void setMouseCoords(int x, int y);
	bool wasKeyDown(unsigned int keyID);

	
};
