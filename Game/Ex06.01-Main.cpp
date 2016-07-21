#include "Game.h"

int main(int argc, char ** argv) {

	Game game("ENTI Rally", 1280,  800,true,60,false);
	try {
		game.start();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}