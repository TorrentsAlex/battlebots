#pragma once
#include <string>
#include <iostream>

#include "FileReader.h"
#include "Geometry.h"
#include "json/json.h"

#include "Scene.h"

using namespace std;
//using json = nlohmann::json;

class SceneCreator {
private:
public:
	SceneCreator();
	~SceneCreator();

	Scene createScene(string file);
};

