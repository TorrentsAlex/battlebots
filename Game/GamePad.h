#pragma once

struct GamePad {

	SDL_Joystick* gameController;


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
	}
};
