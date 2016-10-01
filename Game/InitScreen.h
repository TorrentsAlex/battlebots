#pragma once
#include "BaseScreen.h"
#include "Scene.h"
#include "ButtonManager.h"
#include "GameController.h"


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

	ButtonManager iBManager;
	vector<Button> iButtons;


public:

};

