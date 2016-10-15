#pragma once

#include <Thread>
#include <future>

#include "TurriIncludes.h"

using namespace std;
//This class manages the game execution
class Game : public BaseScreen {
public:

private:

	void init() override;
	void input() override;
	void update() override;
	void render() override;
	void clean() override;

	Scene gScene;
	Character* robot1;

};