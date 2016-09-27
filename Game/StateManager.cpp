#include "StateManager.h"


void StateManager::update() {
	currentState->update();
}

void StateManager::render() {
	currentState->render();
}

void StateManager::input() {
	currentState->input();
}

void StateManager::clean() {
	if (currentState != nullptr) {
		currentState->clean();
		delete currentState;
	}
}

void StateManager::changestate(BaseScreen * newState) {
	if (currentState != nullptr) {
		currentState->clean();
		delete currentState;
	}
	currentState = newState;
	currentState->init();
}
