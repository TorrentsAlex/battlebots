#pragma once
#ifndef  TURRI_WORLD_OBJECTS
#define TURRI_WORLD_OBJECTS

#include "TurriIncludes.h"

class WorldObjects  {
private:


	WorldObjects();

	Character* player1;
	Character* player2;
	Character* player3;
	Character* player4;

	Scene* currentScene;
	Scene* lastScene;

	
	void collisionDetection();

	void executeInput(Character& character);
public:	
	
	static WorldObjects& Instance() {
		static WorldObjects instance;
		return instance;
	}
	WorldObjects(WorldObjects const&) = delete;
	void operator=(WorldObjects const&) = delete;

	void clean();
	void render();
	void update();
	void handleInputs();

	void setCollisionsToWorld();

	Scene& getCurrentScene();
	Character* getPlayerAt(int current);


};
#endif // ! TURRI_WORLD_OBJECTS