#pragma once
#include "BaseScreen.h"
#include "Scene.h"
#include "ButtonManager.h"
#include "GameController.h"
#include "TurriFramework.h"

class OptionsScreen: public BaseScreen {
private:
	void init() override;
	void input() override;
	void update() override;
	void render() override;
	void clean() override;

	Scene* optionsScene;
	
	ButtonManager BManager;
	GamePad* gamePad;

public:
	
};

