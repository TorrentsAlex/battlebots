#include "WorldObjects.h"

#include <thread>

WorldObjects::WorldObjects() {
	currentScene = new Scene();
	lastScene = new Scene();
	player1 = new Character();
	player2 = new Character();
	player3 = new Character();
	player4 = new Character();
}

void WorldObjects::clean() {
	if (player1) {
		player1->clean();
		delete player1;
	}
	if (player2) {
		player2->clean();
		delete player2;
	}
	if (player3) {
		player3->clean();
		delete player3;
	}
	if (player4) {
		player4->clean();
		delete player4;
	}
	if (currentScene) {
		currentScene->clean();
		delete currentScene;
	}
	if (lastScene) {
		lastScene->clean();
		delete lastScene;
	}
}

void WorldObjects::handleInputs() {
	for (int i = 0; i < playersToRender.size(); i++) {
		TurriFramework::Instance().executeInput(*playersToRender.at(i));
	}
}

void WorldObjects::collisionDetection() {

}

/*
	Update all scene, including the characters
*/
void WorldObjects::update() {
	
	// First check collision
	collisionDetection();


	// update the scene
	for (int i = 0; i < playersToRender.size(); i++) {
		playersToRender.at(0)->update();
	}
	// Update objects of the scene
}

/*
	Send objects to render into the screen to OpenGL
*/
void WorldObjects::render() {

	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();

	TurriFramework::Instance().renderLights(currentScene->getLights());

	TurriFramework::Instance().renderScene(*currentScene);

	if (player1->inGame) {
		TurriFramework::Instance().renderEntity(*player1);
	}
	if (player2->inGame) {
		TurriFramework::Instance().renderEntity(*player2);
	}
	if (player3->inGame) {
		TurriFramework::Instance().renderEntity(*player3);
	}
	if (player4->inGame) {
		TurriFramework::Instance().renderEntity(*player4);
	}

	TurriFramework::Instance().disableLights();

	TurriFramework::Instance().renderEntity(currentScene->getSkyBox());
	TurriFramework::Instance().stopRender();
}

Character* WorldObjects::getPlayerAt(int current) {
	switch (current) {
	case 0:
		return player1;
	case 1:
		return player2;
	case 2:
		return player3;
	case 3:
		return player4;
	default:
		return nullptr;
		break;
	}
}

Scene* WorldObjects::getCurrentScene() {
	return currentScene;
}

/**
	These 2 methods are for render the players in game 
*/
void WorldObjects::addCharacterToRender(Character& character) {
	playersToRender.push_back(&character);
}

void WorldObjects::cleanCharactersToRender() {
	playersToRender.clear();
}
