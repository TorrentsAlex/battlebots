#include "WorldCollision.h"

#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

void WorldCollision::init() {
	btBroadphaseInterface* broadPhase = new btDbvtBroadphase();
	
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);	
	
	// Include btGImpactCollisionAlgorithm
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	
	wDynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);

	wDynamicWorld->setGravity(btVector3(0, -10, 0));
}

void WorldCollision::clean() {
	delete wDynamicWorld;
}