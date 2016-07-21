#pragma once
#include <iostream>
#include "Object.h"

class Immovable: public Object {
protected:

public:
	Immovable();
	Immovable(OBJ* mesh, GameObject gameObject);
	~Immovable();	
};

