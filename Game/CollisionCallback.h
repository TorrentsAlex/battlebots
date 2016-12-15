#ifndef TURRI_COLLISIONCALLBACK
#define TURRI_COLLISIONCALLBACK

#include <btBulletCollisionCommon.h>

class CollisionCallback : public btCollisionWorld::ContactResultCallback {
public:
	CollisionCallback();
	~CollisionCallback();
};


#endif // TURRI_COLLISIONCALLBACK