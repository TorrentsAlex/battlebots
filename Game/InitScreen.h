#pragma once
#include "BaseScreen.h"
#include "Scene.h"
#include "Button.h"
#include "GameController.h"

enum class InitState {START, OPTIONS};

class InitScreen : public BaseScreen {
private:
	
	void init() override;
	void input() override;
	void update() override;
	void render() override;
	void clean() override;
	void goToOptions();
	void goToPlayers();

	Scene menuScene;

	vector<Button> iButtons;

	InitState initState;

public:

};

