#pragma once

#include "TurriIncludes.h"

class StateManager {
public:
	void update();
	void render();
	void input();
	void clean();

	void changestate(BaseScreen* newState);
private:
	BaseScreen* currentState = nullptr;
}; 

