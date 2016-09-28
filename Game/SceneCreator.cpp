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
	OBJ objSky = Geometry::LoadModelFromFile(json["sky"]["object"].asString());
	GLuint textureSky = TextureManager::Instance().getTextureID(json["sky"]["texture"].asString());
	newScene.setSkyBox(objSky, textureSky);

	cout << "terrain..." << endl;
	// Terrain
	OBJ objTerrain = Geometry::LoadModelFromFile(json["terrain"]["object"].asString());
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
	OBJ objDecoration = Geometry::LoadModelFromFile(json["decoration"]["object"].asString());
	GLuint textureDecoration = TextureManager::Instance().getTextureID(json["decoration"]["texture"].asString());
	vector<GameObject> vectorDecoration = Geometry::LoadGameElements(json["decoration"]["elements"].asString());

	Entity entity;
	entity.setOBJ(objDecoration);

	vector<Entity> vEntityDecorations;
	for (GameObject gODecoration : vectorDecoration) {
		gODecoration._scale *= 20.0f;
		gODecoration._translate.x *= 1.0f;
		gODecoration._translate.y *= 1.0f;

		entity.setMaterial(terrainMaterial);
		entity.setTextureId(textureDecoration);
		entity.setGameObject(gODecoration);

		vEntityDecorations.push_back(entity);
	}
	
	// Lights
	vector<Light> sceneLights;
	Json::Value ligsfds = json["lights"];
	Light l;
		// ambient
	glm::vec3 ambient;
	ambient.r = json["lights"]["ambient"]["r"].asFloat();
	ambient.g = json["lights"]["ambient"]["g"].asFloat();
	ambient.b = json["lights"]["ambient"]["b"].asFloat();
	l.setAmbient(ambient);
	
	glm::vec3 diffuse;
	diffuse.r = json["lights"]["diffuse"]["r"].asFloat();
	diffuse.g = json["lights"]["diffuse"]["g"].asFloat();
	diffuse.b = json["lights"]["diffuse"]["b"].asFloat();

	glm::vec3 specular;
	specular.r = json["lights"]["specular"]["r"].asFloat();
	specular.g = json["lights"]["specular"]["g"].asFloat();
	specular.b = json["lights"]["specular"]["b"].asFloat();

	// position
	if (!json["lights"]["position"].isNull()) {
		l.setPosition(glm::vec3(json["lights"]["position"]["x"].asFloat(), json["lights"]["position"]["y"].asFloat(), json["lights"]["position"]["z"].asFloat()));
	}

	// direction
	//if (json["lights"]["direction"].isObject()) {
		glm::vec3 direction;
		direction.x = json["lights"]["direction"]["x"].asFloat();
		direction.y = json["lights"]["direction"]["y"].asFloat();
		direction.z = json["lights"]["direction"]["z"].asFloat();
		l.setDirection(direction);
	//}


	sceneLights.push_back(l);
	newScene.setLights(sceneLights);
	newScene.setDecoration(vEntityDecorations);

	return newScene;
}