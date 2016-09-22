#pragma once
#include <string>
#include <iostream>

#include "FileReader.h"
#include "json/json.h"

#include "Scene.h"

using namespace std;
//using json = nlohmann::json;

class SceneCreator {
private:
	Json::Value root;
public:
	SceneCreator();
	~SceneCreator();

	void createScene(string file);
};

