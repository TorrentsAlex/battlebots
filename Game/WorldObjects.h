#pragma once
#include "WorldCollision.h"

class WorldObjects: WorldCollision {
private:
	WorldObjects();

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

	void addCharacterToRender(Character& character);
	void cleanCharactersToRender();
	

	Scene* getCurrentScene();
	Character* getPlayerAt(int current);


};

