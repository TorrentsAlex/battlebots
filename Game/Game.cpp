#include "Game.h"

#include "SceneObjects.h"

void Game::init() {
	
	cout << "init game" << endl;
	gScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");
	
	OBJ robotOBJ = Geometry::LoadModelFromFile("./resources/objects/robot_01.obj");
	GameObject robotObject;
	robotObject._angle = 0;
	robotObject._rotation = glm::vec3(0, 0, 1);
	robotObject._translate = glm::vec3(-40, -40, 0);
	robotObject._scale = glm::vec3(1, 1, 1);
	
	Material robotMaterial;
	robotMaterial.ambient = glm::vec3(1, 1, 1);
	robotMaterial.diffuse = glm::vec3(1, 1, 1);
	robotMaterial.specular = glm::vec3(1, 1, 1);
	
	robot1 = new Character();
	robot1->setGameObject(robotObject);
	robot1->setOBJ(robotOBJ);
	robot1->setMaterial(robotMaterial);
	robot1->setTextureId(TextureManager::Instance().getTextureID("./resources/images/robot01_txt.png"));
	
	robot1->name = "Alex";

	robot1->vectorForward = glm::vec3(0, -1, 0);

	InputManager::Instance().getGameController(*robot1->getGamePad());

	
}

void Game::input() {
	TurriFramework::Instance().executeInput(*robot1);
}

void Game::update() {
	robot1->update();
}

void Game::render() {
	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();

	TurriFramework::Instance().renderLights(gScene.getLights());
	TurriFramework::Instance().renderScene(gScene);
	
	TurriFramework::Instance().disableLights();
	
	TurriFramework::Instance().renderEntity(*robot1);
	
	TurriFramework::Instance().renderEntity(gScene.getSkyBox());
	TurriFramework::Instance().stopRender();
}

void Game::clean() {
	gScene.clean();
	robot1->clean();
	delete robot1;
}

