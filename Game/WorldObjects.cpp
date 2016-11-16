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
	for (int i = 0; i < playersToRender.size(); i++) {
		TurriFramework::Instance().executeInput(*playersToRender.at(i));
	}
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
		btCollisionShape* colShape = new btBoxShape(btVector3(widht, height, hight));

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
		player1->setCollisionObject(collObject);
		wDynamicWorld->applyGravity();
	}

}

void WorldObjects::collisionDetection() {
	wDynamicWorld->stepSimulation(1/60.0f);
	//print positions of all objects
	for (int j = wDynamicWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = wDynamicWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);

		}
		else
		{
			trans = obj->getWorldTransform();
		}
		printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
	/*int numManifolds = wDynamicWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; ++i) {
		btPersistentManifold* manifold = wDynamicWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* object0 = manifold->getBody0();
		const btCollisionObject* object1 = manifold->getBody1();
		int numContacts = manifold->getNumContacts();
		for (int j = 0; j<numContacts; j++) {
			btManifoldPoint& pt = manifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
		}
	}*/
}

/*
	Update all scene, including the characters
*/
void WorldObjects::update() {
	// First check collision
	collisionDetection();


	// update the scene
	for (int i = 0; i < playersToRender.size(); i++) {
		playersToRender.at(i)->update();
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
