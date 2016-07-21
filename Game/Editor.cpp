#include "Editor.h"

Editor::Editor() {
}


Editor::~Editor() {
}

void Editor::playerCommands(InputManager iManager) {
	if (iManager.isKeyPressed(SDLK_t)) {
		saveCurrentObjects();
		objectType = ObjectType::TREE;
		cout << "Tree mode" << endl;
	}
	if (iManager.isKeyPressed(SDLK_r)) {
		saveCurrentObjects();
		objectType = ObjectType::ROCK;
		cout << "Rock mode" << endl;
	}
	if (iManager.isKeyPressed(SDLK_d)) {
		saveCurrentObjects();
		objectType = ObjectType::TERRAIN;
		cout << "Terrain mode" << endl;

	}
}

void Editor::newCoord(glm::vec2 mouseCoords) {
	std::vector<float> newObject;
	if (editorCoords.size() != 0) {
		if (editorCoords.back().at(0) == mouseCoords.x &&
			editorCoords.back().at(1) == mouseCoords.y) {
			return;
		}
	}
	cout << "New object at:" << mouseCoords.x << "/" << mouseCoords.y << endl;

	switch (objectType) {
		case ObjectType::TREE:
		case ObjectType::ROCK:
			newObject.push_back(mouseCoords.x); // x 
			newObject.push_back(mouseCoords.y); // y
			newObject.push_back(0); // z
			newObject.push_back(rand() % 360); // angle
			newObject.push_back(0); // x rotation
			newObject.push_back(0); // y rotation
			newObject.push_back(1); // z rotation
			newObject.push_back(1); // x scale
			newObject.push_back(1); // y scale
			newObject.push_back(1); // z scale
			break;
		case ObjectType::TERRAIN:
			newObject.push_back(mouseCoords.x); // x 
			newObject.push_back(mouseCoords.y); // y
			newObject.push_back(0); // z
	}
	// Save the new object in vector
	editorCoords.push_back(newObject);
}

void Editor::saveCurrentObjects() {
	std::string fileName;
	switch (objectType) {
		case ObjectType::TREE:
			fileName = treeFile;
			break;
		case ObjectType::ROCK:
			fileName = rockFile;
			break;
		case ObjectType::TERRAIN:
			fileName = terrainFile;
	}
	FileReader::SaveArrayToFile(editorCoords, fileName);
	cout << "Saved " << editorCoords.size() << " objects" << endl;
	editorCoords.clear();
}