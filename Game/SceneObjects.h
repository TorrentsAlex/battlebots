#pragma once
#include "TurriIncludes.h"

class SceneObjects {
private:
	SceneObjects();

	Character* player1;
	Character* player2;
	Character* player3;
	Character* player4;

	Scene* currentScene;
	Scene* lastScene;

public:	
	
	static SceneObjects& Instance() {
		static SceneObjects instance;
		return instance;
	}
	SceneObjects(SceneObjects const&) = delete;
	void operator=(SceneObjects const&) = delete;

	void clean();

	Scene* getCurrentScene();
	Character* getPlayerAt(int current);
};

