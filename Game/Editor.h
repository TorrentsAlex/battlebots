#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "InputManager.h"
#include "FileReader.h"

enum class ObjectType { TREE, ROCK, TERRAIN };

class Editor {
private:
	ObjectType objectType = ObjectType::TREE;
	std::vector<std::vector<float>> editorCoords;


	// The path of resources
	std::string treeFile = "./resources/Scenes/treeScene.txt";
	std::string rockFile = "./resources/Scenes/rockScene.txt";
	std::string terrainFile = "./resources/Scenes/terrainVertex.txt";
public:
	Editor();
	~Editor();

	void newCoord(glm::vec2 mouseCoords);
	void saveCurrentObjects();
	void playerCommands(InputManager iManager);

};

