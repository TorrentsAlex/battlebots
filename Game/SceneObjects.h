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
	
	glm::vec2 maxLimits;
	glm::vec2 minLimits;
	std::vector<Character*> playersToRender;

	void collisionDetection();
public:	
	
	static SceneObjects& Instance() {
		static SceneObjects instance;
		return instance;
	}
	SceneObjects(SceneObjects const&) = delete;
	void operator=(SceneObjects const&) = delete;

	void clean();
	void render();
	void update();
	void handleInputs();

	void addCharacterToRender(Character& character);
	void cleanCharactersToRender();
	

	Scene* getCurrentScene();
	Character* getPlayerAt(int current);


};

