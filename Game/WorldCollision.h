#pragma once

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class WorldCollision {
private:

	WorldCollision() {};
	
	btDiscreteDynamicsWorld* wDynamicWorld;

public:
	static WorldCollision& Instance() {
		static WorldCollision instance;
		return instance;
	}
	WorldCollision(WorldCollision const&) = delete;
	void operator=(WorldCollision const&) = delete;

	void init();

	void clean();
}; 

