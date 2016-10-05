#pragma once
#include <string>
#include <iostream>

#include "FileReader.h"
#include "Geometry.h"
#include "json/json.h"

#include "Scene.h"

#include "Light.h"

#include "Button.h"

using namespace std;
//using json = nlohmann::json;

class SceneCreator {
private:

	SceneCreator() {};
public:
	static SceneCreator& Instance() {
		static SceneCreator instance;	// Guaranteed to be destroyed.
										// Instantiated on first use.
		return instance;
	}
	// Singleton Pattern - Delete Copy constructor and operator=
	SceneCreator(SceneCreator const&) = delete;
	void operator=(SceneCreator const&) = delete;

	Scene createScene(string file);
	vector<Button> createButtons(string file);
};

