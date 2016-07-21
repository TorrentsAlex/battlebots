#pragma once
#include "Vertex.h"
#include <vector>
#include "GameObject.h"
#include "FileReader.h"
#include <thread>

#define BLUE_CUBE 0
#define RED_CUBE 1
#define WHITE_CUBE 2
#define RED_PYRAMID 3
#define GREY_CAR 4
#define NUMBASICOBJECTS 4

//This class stores and manipulates all the objects loaded from the text file
class Geometry {
	Vertex * _verticesData[NUMBASICOBJECTS];
	int _numVertices[NUMBASICOBJECTS];
	std::vector <GameObject> _listOfObjects;


public:
	Geometry();
	~Geometry();
	void loadCube(int CUBE, glm::vec3 color);
	void loadPyramid(int CUBE, glm::vec3 color);
	void loadGameElements(char fileName[100]);
	Vertex * getData(int objectID);
	int getNumVertices(int objectID);
	int getNumGameElements();
	GameObject & getGameElement(int objectID);


	static  std::vector<GameObject> LoadGameElements(std::string file);
	static OBJ* LoadModelFromFile(std::string file, glm::vec3 color);
	
};