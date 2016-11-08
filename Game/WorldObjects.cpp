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
	if (player1->getGamePad()->gameController) {
		InputManager::Instance().handleInput(*player1->getGamePad());
	}
	if (player2->getGamePad()->gameController) {
		InputManager::Instance().handleInput(*player2->getGamePad());
	}
	if (player3->getGamePad()->gameController) {
		InputManager::Instance().handleInput(*player3->getGamePad());
	}
	if (player4->getGamePad()->gameController) {
		InputManager::Instance().handleInput(*player4->getGamePad());
	}
	
	
	if (player1->inGame) {
		executeInput(*player1);
	}
	if (player2->inGame) {
		executeInput(*player2);
	}
	if (player3->inGame) {
		executeInput(*player3);
	}
	if (player4->inGame) {
		executeInput(*player4);
	}

	if (InputManager::Instance().isKeyPressed(SDLK_e)) {
		Json::Reader reader;

		string jsonString = FileReader::LoadStringFromFile("./resources/materials/lights/pointlight_middle.json");
		Json::Value json;
		std::vector<Light> lights = currentScene->getLights();
		
		glm::vec3 ambient, diffuse, specular, position;

		reader.parse(jsonString, json);
		position.r = json["position"]["x"].asFloat();
		position.g = json["position"]["y"].asFloat();
		position.b = json["position"]["z"].asFloat();

		ambient.r = json["ambient"]["r"].asFloat();
		ambient.g = json["ambient"]["g"].asFloat();
		ambient.b = json["ambient"]["b"].asFloat();

		diffuse.r = json["diffuse"]["r"].asFloat();
		diffuse.g = json["diffuse"]["g"].asFloat();
		diffuse.b = json["diffuse"]["b"].asFloat();

		specular.r = json["specular"]["r"].asFloat();
		specular.g = json["specular"]["g"].asFloat();
		specular.b = json["specular"]["b"].asFloat();
		
		string type = json["type"].asString();
		if (type.compare("point") == 0) {
			float constant = json["constant"].asFloat();
			float linear = json["linear"].asFloat();
			float quadratic = json["quadratic"].asFloat();
			lights.at(3).setConstant(constant);
			lights.at(3).setLinear(linear);
			lights.at(3).setQuadratic(quadratic);
		}
		lights.at(3).setPosition(position);

		lights.at(3).setPower(json["power"].asFloat());
		lights.at(3).setType(type);
		lights.at(3).setAmbient(ambient);
		lights.at(3).setDiffuse(diffuse);
		lights.at(3).setSpecular(specular);

		currentScene->setLights(lights);
		cout << "directional white values readed and saved!!" << endl;
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
		playersToRender.at(1)->update();
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


void WorldObjects::executeInput(Character& character) {
	// Joystick
	std::vector<JoystickCommand*> joystickComm = InputManager::Instance().getGamePadJoysticks(*character.getGamePad());
	for (JoystickCommand* jcom : joystickComm) {
		if (jcom) {
			jcom->execute(character);
		}
	}
	// Buttons
	std::vector<Command*> commands = InputManager::Instance().getGamePadCommand(*character.getGamePad());
	for (Command* com : commands) {
		if (com) {
			com->execute(character);
		}
	}
}