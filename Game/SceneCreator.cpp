#include "SceneCreator.h"



Scene SceneCreator::createScene(string file) {
	cout << "creating scene" << endl;
	Scene newScene;
	Json::Reader reader; 
	Json::Value json;

	// Load File and save it into string
	string jsonString = FileReader::LoadStringFromFile(file);
	// Parse the string into json
	reader.parse(jsonString, json);
	cout << "skybox..." << endl;

	// SkyBox
	OBJ objSky = Geometry::LoadModelFromFile(json["sky"]["object"].asString(), true);
	GLuint textureSky = TextureManager::Instance().getTextureID(json["sky"]["texture"].asString());
	newScene.setSkyBox(objSky, textureSky);

	cout << "terrain..." << endl;
	// Terrain
	OBJ objTerrain = Geometry::LoadModelFromFile(json["terrain"]["object"].asString(), true);
	GLuint textureTerrain = TextureManager::Instance().getTextureID(json["terrain"]["texture"].asString());
	
	// Terrain material
	string jsonMaterialString = FileReader::LoadStringFromFile(json["terrain"]["material"].asString());
	Json::Value jsonMaterial;
	reader.parse(jsonMaterialString, jsonMaterial);
	Material terrainMaterial;
	terrainMaterial.ambient = glm::vec3(jsonMaterial["ambient"]["r"].asFloat(), jsonMaterial["ambient"]["g"].asFloat(), jsonMaterial["ambient"]["b"].asFloat());
	terrainMaterial.diffuse = glm::vec3(jsonMaterial["diffuse"]["r"].asFloat(), jsonMaterial["ambient"]["g"].asFloat(), jsonMaterial["ambient"]["b"].asFloat());
	terrainMaterial.specular = glm::vec3(jsonMaterial["specular"]["r"].asFloat(), jsonMaterial["ambient"]["g"].asFloat(), jsonMaterial["ambient"]["b"].asFloat());
	terrainMaterial.shininess = jsonMaterial["shininess"].asFloat();
	newScene.setTerrain(objTerrain, textureTerrain, terrainMaterial);

	cout << "decoration..." << endl;
	// Decoration
	OBJ objDecoration = Geometry::LoadModelFromFile(json["decoration"]["object"].asString(), true);
	GLuint textureDecoration = TextureManager::Instance().getTextureID(json["terrain"]["texture"].asString());
	vector<GameObject> vectorDecoration = Geometry::LoadGameElements(json["decoration"]["elements"].asString());

	Entity entity;
	entity.setOBJ(objDecoration);

	vector<Entity> vEntityDecorations;
	for (GameObject gODecoration : vectorDecoration) {
		gODecoration._scale *= 20.0f;
		gODecoration._translate.x *= 10.0f;
		gODecoration._translate.y *= 10.0f;

		entity.setMaterial(terrainMaterial);
		entity.setTextureId(textureDecoration);
		entity.setGameObject(gODecoration);

		vEntityDecorations.push_back(entity);
	}
		
	newScene.setDecoration(vEntityDecorations);


	return newScene;
}