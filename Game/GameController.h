#pragma once
#include <string>

#include "TurriIncludes.h"


using namespace std;
enum class GameState { MENU, OPTIONS, PLAYERS, MODE, ARENA, PLAY, EXIT, FINISH };

class GameController {
private:
	GameState gGameState;
	StateManager gCurrentScreen;
	
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

	// Change current state
	void changeState(GameState nextState);
	// init methods	
	void init();
	
	void input();
	void update();
	void render();

	void quit();
};

