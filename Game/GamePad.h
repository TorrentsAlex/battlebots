#pragma once
#include "TurriIncludes.h"

struct GamePadButtonState {
	Uint8 wasDown;
	Uint8 isDown;
};

struct GamePad {

	SDL_GameController* gameController;

	std::unordered_map<unsigned int, bool> _previousKeyMap;
	std::unordered_map<unsigned int, bool> _keyMap;

	// Commands
	Command* iButton_A;
	Command* iButton_X;
	Command* iButton_Y;
	Command* iButton_B;

	Command* iButton_UP;
	Command* iButton_DOWN;
	Command* iButton_RIGHT;
	Command* iButton_LEFT;

	Command* iButton_LB;
	Command* iButton_RB;

	Command* iButton_SELECT;
	Command* iButton_START;

	Command* iButton_L3;
	Command* iButton_R3;

	JoystickCommand* iJoystick_LEFT; 
	JoystickCommand* iJoystick_RIGHT;

	JoystickCommand* iJoystick_LEFT_SHOULDER; 
	JoystickCommand* iJoystick_RIGHT_SHOULDER;

	GamePadButtonState dPadUp;
	GamePadButtonState dPadDown;
	GamePadButtonState dPadLeft;
	GamePadButtonState dPadRight;
	GamePadButtonState start;
	GamePadButtonState select;
	GamePadButtonState buttonA;
	GamePadButtonState buttonB;
	GamePadButtonState buttonX;
	GamePadButtonState buttonY;
	GamePadButtonState leftShoulder;
	GamePadButtonState rightShoulder;

	void clean() {
		delete iButton_A;
		delete iButton_X;
		delete iButton_Y;
		delete iButton_B;

		delete iButton_UP;
		delete iButton_DOWN;
		delete iButton_RIGHT;
		delete iButton_LEFT;

		delete iButton_LB;
		delete iButton_RB;

		delete iButton_SELECT;
		delete iButton_START;

		delete iButton_L3;
		delete iButton_R3;

		delete iJoystick_LEFT;
		delete iJoystick_RIGHT;

		delete iJoystick_LEFT_SHOULDER;
		delete iJoystick_RIGHT_SHOULDER;
	}
};
