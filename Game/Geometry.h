#pragma once
#include "Vertex.h"
#include <vector>
#include "GameObject.h"
#include "FileReader.h"
#include <thread>

class Geometry {
public:

	static  std::vector<GameObject> LoadGameElements(std::string file);

	static OBJ LoadModelFromFile(std::string file);
};