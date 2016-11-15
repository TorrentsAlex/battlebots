#pragma once

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include "TurriIncludes.h"

class WorldCollision {
protected:
	WorldCollision();
	~WorldCollision();
	btDiscreteDynamicsWorld* wDynamicWorld;
	btCollisionWorld* wCollisionWorld;

private:

public:
	
	void init();

	void clean();
}; 

