#pragma once
#include <string>
#include <iostream>

#include "FileReader.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class SceneCreator {
private:
public:
	SceneCreator();
	~SceneCreator();

	void createScene(string file);
};

