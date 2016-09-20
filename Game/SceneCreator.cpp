#include "SceneCreator.h"



SceneCreator::SceneCreator() {
}


SceneCreator::~SceneCreator() {
}

void SceneCreator::createScene(string file) {

	string jsonString = FileReader::LoadStringFromFile(file);
	//json myjson(jsonString); //;= json::parse(jsonString);
	Json::Reader reader;

	reader.parse(jsonString, root);
	cout << root.get("encoding", "none").asString() << endl;

}