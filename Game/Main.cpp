#include <Windows.h>

#include "Game.h"

#include "GameController.h"

int main(int argc, char ** argv) {
	// Hide the command line
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	TurriFramework::Instance().init("Beard Knights", 1280, 800, true, 60, false);

	GameController::Instance().init();
	try {
		while(TurriFramework::Instance().isRunning()) {
			TurriFramework::Instance().startSync();

			GameController::Instance().input();
			GameController::Instance().update();
			// step world bullet physics
			GameController::Instance().render();

			TurriFramework::Instance().endSync();
		}
	} catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		system("pause");
	}

	TextureManager::Instance().deleteTextures();
	InputManager::Instance().clean();
	GameController::Instance().clean();

	//TurriFramework::Instance().clean();

	return 0;
}