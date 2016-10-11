#include "InputManager.h"


void InputManager::init() {
	pad1 = new GamePad();
	//SDL_GameControllerAddMappingsFromFile("./resources/gamecontrollerdb.txt");
	if (SDL_NumJoysticks() < 1) {
		printf("Warning: No joysticks connected!\n");
	} else {
		//Load joystick
		pad1->gameController = SDL_GameControllerOpen(0);
		if (pad1->gameController == NULL) {
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		} else {
			cout << "open controller " << pad1->gameController << endl;
		}
	}
	// mapping 
	pad1->iButton_A = new JumpCommand();
	pad1->iButton_X = new ShootCommand();	
	pad1->iButton_Y = new Y();
	pad1->iButton_B = new B();

	pad1->iButton_UP = new UP();
	pad1->iButton_DOWN = new Down();
	pad1->iButton_RIGHT = new Right();
	pad1->iButton_LEFT = new Left();

	pad1->iButton_LB = new Lb();
	pad1->iButton_RB = new RB();

	pad1->iButton_SELECT = new Select();
	pad1->iButton_START = new Start();

	pad1->iButton_L3 = new L3();
	pad1->iButton_R3 = new R3();
}

void InputManager::clean() {
	SDL_GameControllerClose(pad1->gameController);
	pad1->clean();
	delete pad1;
}

	//Copy the current key states to a data structure that contains the previous states
void InputManager::handleInput() {
		//Loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
		//C++ 11 introduces the concept "for each loop" on data structures based on iterators that has begin and end
	for (auto & it : _keyMap) {
		//Copy in the position of the key (it->first), the value (it->second)
		_previousKeyMap[it.first] = it.second;
	}

	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			TurriFramework::Instance().quit();
			break;
		case SDL_KEYDOWN:
			pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			releaseKey(evnt.key.keysym.sym);
			break;
		}
	}
}

Command* InputManager::getGamePadCommand() {

	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_A))return pad1->iButton_A;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_B))return pad1->iButton_B;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_X))return pad1->iButton_X;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_Y))return pad1->iButton_Y;

	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN))return pad1->iButton_DOWN;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_DPAD_UP))return pad1->iButton_UP;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))return pad1->iButton_RIGHT;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT))return pad1->iButton_LEFT;
	
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_LEFTSTICK))return pad1->iButton_L3;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_RIGHTSTICK))return pad1->iButton_R3;

	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_BACK))return pad1->iButton_SELECT;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_START))return pad1->iButton_START;
	
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER))return pad1->iButton_LB;
	if (SDL_GameControllerGetButton(pad1->gameController, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))return pad1->iButton_RB;

	return nullptr;
}

void InputManager::pressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	_keyMap[keyID] = false;
}

void InputManager::setMouseCoords(int x, int y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()) {
		// Found the key
		return it->second;
	} else {
		// Didn't find the key
		return false;
	}
}

bool InputManager::wasKeyDown(unsigned int keyID) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _previousKeyMap.find(keyID);
	if (it != _previousKeyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

bool InputManager::isKeyPressed(unsigned int keyID) {
		//Check if it was pressed current frame and not last frame
	if ((isKeyDown(keyID)) && (wasKeyDown(keyID) == false)) {
		return true;
	}
	return false;
}	

int InputManager::getAxis() {
	return -1;//SDL_JoystickGetAxis(pad1->gameController, 0);
}

unsigned int InputManager::keyPressed() {
	unsigned int key = -1;
	for (int i = 0; i < _keyMap.size(); i++) {
		if ((isKeyDown(_keyMap.at(i))) && (wasKeyDown(_keyMap.at(i)) == false)) {
			key = _keyMap.at(i);
		}
	}
	return key;
}

unsigned int InputManager::keyDown() {
	return -1;
}