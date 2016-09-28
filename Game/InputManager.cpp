#include "InputManager.h"


void InputManager::init() {
	if (SDL_NumJoysticks() < 1) {
		printf("Warning: No joysticks connected!\n");
	} else {
		//Load joystick
		gameController = SDL_JoystickOpen(0);
		if (gameController == NULL) {
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		} 
	}
}

void InputManager::clean() {
	SDL_JoystickClose(gameController);

}


	//Copy the current key states to a data structure that contains the previous states
void InputManager::update() {
		//Loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
		//C++ 11 introduces the concept "for each loop" on data structures based on iterators that has begin and end
	for (auto & it : _keyMap) {
		//Copy in the position of the key (it->first), the value (it->second)
		_previousKeyMap[it.first] = it.second;
	}
	//for (auto it = _keyMap.begin(); it != _keyMap.end(); it++) {
	//	_previousKeyMap[it->first] = it->second;
	//}		
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
	return 	SDL_JoystickGetAxis(gameController, 0);
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