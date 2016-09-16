#include <Windows.h>

#include "Game.h"

#include "SceneCreator.h"

int main(int argc, char ** argv) {
	// Hide the command line
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	SceneCreator sceneCr;

	sceneCr.createScene("./resources/Scenes/Scene1.json");

	Game game("BattleBots", 1280,  800,true,60,false);
	try {
		game.start();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}