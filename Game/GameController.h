#pragma once
#include <string>

#include "TurriIncludes.h"
#include "Game.h"

using namespace std;
enum class GameState { INIT, MENU, PLAY, EXIT, FINISH };

class GameController {
private:
	GameState gGameState;
	StateManager gCurrentScreen;
	bool running;

	// Constructor
	GameController() {}

public:

	static GameController& Instance() {
		static GameController instance;	// Guaranteed to be destroyed.
								// Instantiated on first use.
		return instance;
	}
	// Singleton Pattern - Delete Copy constructor and operator=
	GameController(GameController const&) = delete;
	void operator=(GameController const&) = delete;

	// init methods	
	void init();
	
	bool isRunning();

	void input();
	void update();
	void render();
};

