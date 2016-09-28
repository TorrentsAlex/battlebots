#include <Windows.h>

#include "Game.h"
#include "SceneCreator.h"

#include "GameController.h"

int main(int argc, char ** argv) {
	// Hide the command line
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	TurriFramework::Instance().init("BattleBots", 1280, 800, true, 80, true);

	GameController::Instance().init();
	try {
		while(GameController::Instance().isRunning()) {
			TurriFramework::Instance().startSync();

			GameController::Instance().input();
			GameController::Instance().update();
			GameController::Instance().render();

			TurriFramework::Instance().endSync();
		}
	} catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	TextureManager::Instance().deleteTextures();
	//TurriFramework::Instance().clean();

	return 0;
}