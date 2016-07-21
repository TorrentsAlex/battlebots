#include "ErrorManagement.h"
#include <SDL/SDL.h>
#include <iostream>



/*
* Prints out an error message and exits the game
*/
void ErrorManagement::errorRunTime(std::string errorString) {
	cout << errorString << endl;
	cout << "Enter any key to quit..";
	system("pause");
	SDL_Quit();		//It shuts down SDL
	exit(-1);		//It exist the game
}
