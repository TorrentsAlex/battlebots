#pragma once
#include <string>

using namespace std;

class GameController {
private:
	GameController() {}

	bool running;

public:

	static GameController& getInstance() {
		static GameController instance;	// Guaranteed to be destroyed.
								// Instantiated on first use.
		return instance;
	}
	// Singleton Pattern - Delete Copy constructor and operator=
	GameController(GameController const&) = delete;
	void operator=(GameController const&) = delete;

	// init methods	
	void init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS);
	
	bool isRunning();

	void input();
	void update();
	void render();
};

