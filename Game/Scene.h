#pragma once
#include "Car.h"
#include "ParticleSystem.h"
#include "Immovable.h"
#include "Movable.h"
#include "DirectionalLight.h"
#include "Light.h"

#include "FileReader.h"

class Scene {
private:
	Car gCar;
	std::vector<Immovable> gListOfTrees;
	std::vector<Immovable> gListOfRocks;
	std::vector<Immovable> gListOfbarrels;
	std::vector<Movable> gListOfPerson;

	DirectionalLight gDirectionalLight;


	std::vector <Light> lights;

	ParticleSystem gPSystem;
	Immovable gFinish;

	OBJ* gOBJPerson;
	OBJ* gOBJBarrel;
	OBJ* gOBJTree;
	OBJ* gOBJRock;
	OBJ* gOBJTerrain;
	OBJ* gOBJFinish;
	OBJ* gOBJSkyBox;
	OBJ* gOBJDrop;
	OBJ* gOBJRectangle;


public:
	Scene();
	~Scene();
};

