#include "SceneCreator.h"



SceneCreator::SceneCreator() {
}


SceneCreator::~SceneCreator() {
}

void SceneCreator::createScene(string file) {
	Scene newScene;
	Json::Reader reader; 

	// Load File and save it into string
	string jsonString = FileReader::LoadStringFromFile(file);

	reader.parse(jsonString, root);
	cout << "sky texture: "<< root.get("skytexture", "none").asString() << endl;
	cout << "terrain model: " << root["terrain"]["object"]<< endl;
	cout << "terrain texture: " << root["terrain"]["texture"] << endl;



	cout << "decoration object: " << root["decoration"]["object"] << endl;
	cout << "decoration texture: " << root["decoration"]["texture"] << endl;
	cout << "decoration position: " << root["decoration"]["position"] << endl;


	//return scene
}