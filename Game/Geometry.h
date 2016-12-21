#pragma once
#ifndef  TURRI_GEOMETRY
#define TURRI_GEOMETRY

#include "Vertex.h"
#include <vector>
#include "FileReader.h"
#include <thread>

#include "TurriIncludes.h"

class Geometry {
public:

	static  std::vector<GameObject> LoadGameElements(std::string file);

	static OBJ LoadModelFromFile(std::string file);
	static OBJ LoadModelFBXFromFile(std::string file);
};

#endif // ! TURRI_GEOMETRY
