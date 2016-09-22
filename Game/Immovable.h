#pragma once
#include <iostream>
#include "Entity.h"

class Immovable: public Entity {
protected:

public:
	Immovable();
	Immovable(OBJ* mesh, GameObject gameObject);
	~Immovable();	
};

