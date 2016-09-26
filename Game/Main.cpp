#include <Windows.h>

#include "Game.h"
#include "SceneCreator.h"

#include "GameController.h"

int main(int argc, char ** argv) {
	// Hide the command line
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	//Game game("BattleBots", 1280,  800,true,60,false);
	TurriFramework::Instance().init("BattleBots", 1280, 800, true, 60, false);

	GameController::getInstance().init("BattleBots", 1280, 800, true, 60, false);
	try {
		//game.start();
		while(GameController::getInstance().isRunning()) {
			GameController::getInstance().input();
			GameController::getInstance().update();
			GameController::getInstance().render();
		}
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}