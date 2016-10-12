#include "Game.h"

void Game::init() {
	cout << "init game" << endl;
	gScene = SceneCreator::Instance().createScene("../battlebots/Game/resources/scenes/Scene2.json");

	OBJ robotOBJ = Geometry::LoadModelFromFile("../battlebots/Game/resources/objects/robot_01.obj");
	GameObject robotObject;
	robotObject._angle = 0;
	robotObject._rotation = glm::vec3(0, 0, 1);
	robotObject._translate = glm::vec3(-40, -40, 0);
	robotObject._scale = glm::vec3(1, 1, 1);
	
	Material robotMaterial;
	robotMaterial.ambient = glm::vec3(1, 1, 1);
	robotMaterial.diffuse = glm::vec3(1, 1, 1);
	robotMaterial.specular = glm::vec3(1, 1, 1);
	
	robot1 = new Robot();
	robot1->setGameObject(robotObject);
	robot1->setOBJ(robotOBJ);
	robot1->setMaterial(robotMaterial);
	robot1->setTextureId(TextureManager::Instance().getTextureID("../battlebots/Game/resources/images/robot01_txt.png"));

	// Robot 2
	robotObject._translate = glm::vec3(-20, -20, 0);

	robotObject._scale = glm::vec3(3, 3, 3);
	robot2 = new Robot();
	robot2->setGameObject(robotObject);
	robot2->setOBJ(robotOBJ);
	robot2->setMaterial(robotMaterial);
	robot2->setTextureId(TextureManager::Instance().getTextureID("../battlebots/Game/resources/images/robot01_txt.png"));

	robot1->name = "Alex";
	robot2->name = "Turri";

	robot1->vectorForward = glm::vec3(0, -1, 0);
	robot2->vectorForward = glm::vec3(0, -1, 0);

	// Open the controllers

	//InputManager::Instance().getController(*InputManager::Instance().pad1);
	//InputManager::Instance().getController(*InputManager::Instance().pad2);
}

void Game::input() {
	// Joystick
	//std::vector<JoystickCommand*> joystickComm = InputManager::Instance().getGamePadJoysticks(*robot1->gamepad);
	std::vector<JoystickCommand*> joystickComm = InputManager::Instance().getGamePadJoysticks(*InputManager::Instance().pad1);
	for (JoystickCommand* jcom: joystickComm) {
		if (jcom) {
			jcom->execute(*robot1);
		}
	}
	// Buttons
	//std::vector<Command*> commands = InputManager::Instance().getGamePadCommand(*robot1->gamepad);
	std::vector<Command*> commands = InputManager::Instance().getGamePadCommand(*InputManager::Instance().pad1);
	for (Command* com : commands) {
		if (com) {
			com->execute(*robot1);
		}
	}
	//////////////////////////////////////////////////////////
	// PAD 2
	//std::vector<JoystickCommand*> joystickComm2 = InputManager::Instance().getGamePadJoysticks(*robot2->gamepad);
	std::vector<JoystickCommand*> joystickComm2 = InputManager::Instance().getGamePadJoysticks(*InputManager::Instance().pad2);
	for (JoystickCommand* jcom : joystickComm2) {
		if (jcom) {
			jcom->execute(*robot2);
		}
	}	
	// Buttons
	//std::vector<Command*> commands1 = InputManager::Instance().getGamePadCommand(*robot2->gamepad);
	std::vector<Command*> commands1 = InputManager::Instance().getGamePadCommand(*InputManager::Instance().pad2);
	for (Command* com : commands1) {
		if (com) {
			com->execute(*robot2);
		}
	}
}

void Game::update() {
	robot1->update();
	robot2->update();
}

void Game::render() {
	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();

	TurriFramework::Instance().renderLights(gScene.getLights());
		
	TurriFramework::Instance().renderScene(gScene);

	TurriFramework::Instance().disableLights();
	
	TurriFramework::Instance().renderEntity(*robot1);
	TurriFramework::Instance().renderEntity(*robot2);
	
	TurriFramework::Instance().renderEntity(gScene.getSkyBox());
	TurriFramework::Instance().stopRender();
}

void Game::clean() {
	gScene.clean();
}

