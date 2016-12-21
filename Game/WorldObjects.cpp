#include "WorldObjects.h"

#include <thread>

WorldObjects::WorldObjects() {
	currentScene = new Scene();
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
	
	if (player1->inGame) {
		InputManager::Instance().handleInput(player1->getGamePad());
		executeInput(*player1);
	}
	if (player2->inGame) {
		InputManager::Instance().handleInput(player2->getGamePad());
		executeInput(*player2);
	}
	if (player3->inGame) {
		InputManager::Instance().handleInput(player3->getGamePad());
		executeInput(*player3);
	}
	if (player4->inGame) {
		InputManager::Instance().handleInput(player4->getGamePad());
		executeInput(*player4);
	}

	TurriFramework::Instance().moveCameraWithKeyboard();
}

void WorldObjects::setCollisionsToWorld() {
	//btAlignedObjectArray<btCollisionShape*> collisionShapes;
	//btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(70.), btScalar(70.), btScalar(10.)));
	//collisionShapes.push_back(groundShape);

	//btTransform groundTransform;
	//groundTransform.setIdentity();
	//groundTransform.setOrigin(btVector3(0, 0, -10));

	//btScalar mass(0.);

	////rigidbody is dynamic if and only if mass is non zero, otherwise static
	//bool isDynamic = (mass != 0.f);

	//btVector3 localInertia(0, 0, 0);
	//if (isDynamic)
	//	groundShape->calculateLocalInertia(mass, localInertia);

	////using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	//btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	//btRigidBody* body = new btRigidBody(rbInfo);

	////add the body to the dynamics world
	//wDynamicWorld->addRigidBody(body);
	//{
	//	// Add character 1
	//	btCollisionObject* collObject = new btCollisionObject();
	//	glm::vec3 volume = player1->getCollisionVolume();

	//	// widht, height and hight
	//	btCollisionShape* colShape = new btBoxShape(btVector3(volume.x, volume.y, volume.z));
	//	
	//	collObject->setCollisionShape(colShape);
	//	// add to world
	//	collisionShapes.push_back(colShape);
	//	btTransform startTransform;
	//	startTransform.setIdentity();

	//	btScalar	mass(200.f);

	//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//	bool isDynamic = (mass != 0.f);

	//	btVector3 localInertia(0, 0, 0);
	//	if (isDynamic)
	//		colShape->calculateLocalInertia(mass, localInertia);

	//	startTransform.setOrigin(btVector3(0, 0, volume.z/2.0f));
	//	
	//	// Add transform to my object
	//	collObject->setWorldTransform(startTransform);

	//	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//	btDefaultMotionState* myMotionState1 = new btDefaultMotionState(startTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo1(mass, myMotionState1, colShape, localInertia);
	//	btRigidBody* body = new btRigidBody(rbInfo1);
	//	//body->setLinearFactor(btVector3(1, 1, 0));
	//	//body->setCollisionFlags(btCollisionObject::CollisionFlags::CF_CHARACTER_OBJECT);
	//	wDynamicWorld->addRigidBody(body);
	//	btCollisionShape* collShape;

	//	player1->setCollisionObject(body);
	//}
	//// Add decoration

	//{
	//	std::vector<Entity> newDecoration;
	//	for (Entity decor : currentScene->getDecoration()) {

	//		// widht, height and hight
	//		glm::vec3 volume = decor.getCollisionVolume();
	//		btCollisionShape* colShape = new btBoxShape(btVector3(volume.x, volume.y, volume.z));

	//		// add to world
	//		collisionShapes.push_back(colShape);
	//		btTransform startTransform;
	//		startTransform.setIdentity();

	//		btScalar	mass(10.0f);

	//		//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//		bool isDynamic = (mass != 0.f);

	//		btVector3 localInertia(0, 0, 0);
	//		if (isDynamic)
	//			colShape->calculateLocalInertia(mass, localInertia);
	//		
	//		glm::vec3 position = decor.getPosition();
	//		startTransform.setOrigin(btVector3(position.x, position.y, position.z));

	//		// Add transform to my object

	//		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//		btDefaultMotionState* myMotionState1 = new btDefaultMotionState(startTransform);
	//		btRigidBody::btRigidBodyConstructionInfo rbInfo1(mass, myMotionState1, colShape, localInertia);
	//		btRigidBody* body = new btRigidBody(rbInfo1);
	//		
	//		body->setWorldTransform(startTransform);
	//		//body->setLinearFactor(btVector3(1, 1, 0));

	//		wDynamicWorld->addRigidBody(body);

	//		decor.setCollisionObject(body);

	//		newDecoration.push_back(decor);
	//	}
	//	currentScene->setDecoration(newDecoration);

	//}

}

void WorldObjects::collisionDetection() {
	//wDynamicWorld->stepSimulation(1 / 60.0f);

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

	TurriFramework::Instance().renderScene(currentScene);

	if (player1->inGame) {
		TurriFramework::Instance().renderEntityWithBullet(*player1);
	}
	if (player2->inGame) {
		TurriFramework::Instance().renderEntity(player2);
	}
	if (player3->inGame) {
		TurriFramework::Instance().renderEntity(player3);
	}
	if (player4->inGame) {
		TurriFramework::Instance().renderEntity(player4);
	}

	TurriFramework::Instance().disableLights();

	TurriFramework::Instance().renderEntity(&currentScene->getSkyBox());
	
	// Render wireframes
#if _DEBUG
 
	for (Entity decor : currentScene->getDecoration()) {
		TurriFramework::Instance().renderCubeAt(&decor);

	}	if (player1->inGame) {
		TurriFramework::Instance().renderCubeAt(player1);
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
#endif

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

Scene& WorldObjects::getCurrentScene() {
	return *currentScene;
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