#include "Game.h"

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

	robot1.setGameObject(robotObject);
	robot1.setOBJ(robotOBJ);
	robot1.setMaterial(robotMaterial);
	robot1.setTextureId(TextureManager::Instance().getTextureID("./resources/images/robot_01_txt.jpg"));

}

void Game::input() {
}

void Game::update() {
	GameObject robotObject = robot1.getGameObject();
	robotObject._angle += 1.50f;
	robot1.setGameObject(robotObject);

}

void Game::render() {
	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();

	TurriFramework::Instance().renderScene(gScene);

	TurriFramework::Instance().renderRobots(robot1);

	TurriFramework::Instance().stopRender();
}

void Game::clean() {
	gScene.clean();
}

