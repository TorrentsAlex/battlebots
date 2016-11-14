#pragma once

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>


#include "TurriIncludes.h"

class WorldCollision {
protected:
	WorldCollision();
	~WorldCollision();
	btDiscreteDynamicsWorld* wDynamicWorld;
private:

	
public:
	
	void init();

	void clean();
}; 

