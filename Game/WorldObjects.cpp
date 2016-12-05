#include "WorldObjects.h"

#include <thread>

WorldObjects::WorldObjects() {
	WorldCollision::init();
	currentScene = new Scene();
	lastScene = new Scene();
	player1 = new Character();
	player2 = new Character();
	player3 = new Character();
	player4 = new Character();

	unitCube = Geometry::LoadModelFromFile("./resources/objects/cube.obj");
	cubeMaterial.textureMap = TextureManager::Instance().getTextureID("./resources/images/back_green.png");
	cubeMaterial.ambient = glm::vec3(0.25, 0.20725, 0.20725);
	cubeMaterial.diffuse = glm::vec3(0.25, 0.20725, 0.20725);
	cubeMaterial.specular = glm::vec3(0.25, 0.20725, 0.20725);
	cubeMaterial.shininess = 4;

	debug = true;
}

void WorldObjects::clean() {
	WorldCollision::clean();
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
	
	if (player1->inGame) {
		InputManager::Instance().handleInput(*player1->getGamePad());
		executeInput(*player1);
	}
	if (player2->inGame) {
		InputManager::Instance().handleInput(*player2->getGamePad());
		executeInput(*player2);
	}
	if (player3->inGame) {
		InputManager::Instance().handleInput(*player3->getGamePad());
		executeInput(*player3);
	}
	if (player4->inGame) {
		InputManager::Instance().handleInput(*player4->getGamePad());
		executeInput(*player4);
	}

	TurriFramework::Instance().moveCameraWithKeyboard();
}

void WorldObjects::setCollisionsToWorld() {
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(70.), btScalar(70.), btScalar(10.)));
	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, -10));

	btScalar mass(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	wDynamicWorld->addRigidBody(body);
	{
		// Add character 1
		btCollisionObject* collObject = new btCollisionObject();

		// widht, height and hight
		btScalar widht = player1->getOBJ().width.y - player1->getOBJ().width.x;
		btScalar height = player1->getOBJ().lenght.y - player1->getOBJ().lenght.x;
		btScalar hight = player1->getOBJ().high.y - player1->getOBJ().high.x;
		btCollisionShape* colShape = new btBoxShape(btVector3(widht, height, widht/2));

		collObject->setCollisionShape(colShape);
		// add to world
		collisionShapes.push_back(colShape);
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(10000.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(0, 0, 40));

		// Add transform to my object
		collObject->setWorldTransform(startTransform);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState1 = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo1(mass, myMotionState1, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo1);

		wDynamicWorld->addRigidBody(body);
		btCollisionShape* collShape;

		player1->setCollisionObject(body);
	}
	// Add decoration

	{
		std::vector<Entity> newDecoration;
		for (Entity decor : currentScene->getDecoration()) {

			// widht, height and hight
			btScalar widht = decor.getOBJ().width.y - decor.getOBJ().width.x;
			btScalar height = decor.getOBJ().lenght.y - decor.getOBJ().lenght.x;
			btScalar hight = decor.getOBJ().high.y - decor.getOBJ().high.x;
			btCollisionShape* colShape = new btBoxShape(btVector3(widht, height, hight));

			// add to world
			collisionShapes.push_back(colShape);
			btTransform startTransform;
			startTransform.setIdentity();

			btScalar	mass(20.0f);

			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (mass != 0.f);

			btVector3 localInertia(0, 0, 0);
			if (isDynamic)
				colShape->calculateLocalInertia(mass, localInertia);
			
			glm::vec3 position = decor.getPosition();
			startTransform.setOrigin(btVector3(position.x, position.y, position.z));

			// Add transform to my object

			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState1 = new btDefaultMotionState(startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo1(mass, myMotionState1, colShape, localInertia);
			btRigidBody* body = new btRigidBody(rbInfo1);
			body->setWorldTransform(startTransform);

			wDynamicWorld->addRigidBody(body);

			decor.setCollisionObject(body);

			newDecoration.push_back(decor);
		}
		currentScene->setDecoration(newDecoration);

	}

}

void WorldObjects::collisionDetection() {
	wDynamicWorld->stepSimulation(1 / 60.0f);

}

/*
	Update all scene, including the characters
*/
void WorldObjects::update() {
	// First check collision
	collisionDetection();


	// update the scene
	if (player1->inGame) {
		player1->update();
	}
	if (player2->inGame) {
		player2->update();
	}
	if (player3->inGame) {
		player3->update();
	}
	if (player4->inGame) {
		player4->update();
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

	for (Entity decor : currentScene->getDecoration()) {
		TurriFramework::Instance().renderEntityWithBullet(decor);
	}

	if (player1->inGame) {
		TurriFramework::Instance().renderEntityWithBullet(*player1);
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
	
	// Render wireframes
//#if debug
	for (Entity decor : currentScene->getDecoration()) {
		TurriFramework::Instance().renderCubeAt(unitCube, decor.getCollisionObject(), cubeMaterial);

	}	if (player1->inGame) {
		TurriFramework::Instance().renderCubeAt(unitCube, player1->getCollisionObject(), cubeMaterial);
	}
	/*if (player2->inGame) {
		TurriFramework::Instance().renderEntity(*player2);
	}
	if (player3->inGame) {
		TurriFramework::Instance().renderEntity(*player3);
	}
	if (player4->inGame) {
		TurriFramework::Instance().renderEntity(*player4);
	}*/

//#endif

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