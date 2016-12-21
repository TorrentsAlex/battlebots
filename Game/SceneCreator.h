#pragma once
#include <string>
#include <iostream>

#include "FileReader.h"
#include "Geometry.h"
#include "json/json.h"

#include "Scene.h"

#include "Light.h"

#include "Button.h"
#include "Character.h"

using namespace std;
//using json = nlohmann::json;

class SceneCreator {
private:

	SceneCreator() {};

	vector<Light> populateLights(Json::Value lights);
public:
	static SceneCreator& Instance() {
		static SceneCreator instance;	// Guaranteed to be destroyed.
										// Instantiated on first use.
		return instance;
	}
	// Singleton Pattern - Delete Copy constructor and operator=
	SceneCreator(SceneCreator const&) = delete;
	void operator=(SceneCreator const&) = delete;

	void createScene(string file, Scene& newScene);
	vector<Button> createButtons(string file);
	void createCharacters(string file, Character& ch1, Character& ch2, Character& ch3, Character& ch4);
};

