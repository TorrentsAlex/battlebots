#pragma once
// Engine includes
#include "TurriFramework.h"
#include "Scene.h"

// Game includes
#include "Robot.h"

class AllvsAll  {
private:

	Scene arena;
	Robot r1, r2, r3, r4;

public:
	~AllvsAll();

	void setPlayers(std::vector<Robot> players);


};

