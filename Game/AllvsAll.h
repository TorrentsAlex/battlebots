#pragma once
// Engine includes
#include "TurriFramework.h"
#include "Scene.h"
#include "BaseMode.h"

// Game includes
#include "Robot.h"

class AllvsAll : BaseMode {
private:
	TurriFramework tf;

	Scene arena;
	Robot r1, r2, r3, r4;

public:
	~AllvsAll();

	void setPlayers(std::vector<Robot> players);


	virtual void input() override;
	virtual void update() override;
	virtual void render() override;


};

