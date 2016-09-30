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
	Json::Value jsonLights = json["lights"];
	for (int i = 0; i < jsonLights.size(); i++) {
		Light l;
		glm::vec3 ambient, diffuse, specular, position, direction;

		Json::Value currentLight;
		string stringlight = FileReader::LoadStringFromFile(jsonLights[i].asString());
		// Parse the string into json
		reader.parse(stringlight, currentLight);

		// ambient
		ambient.r = currentLight["ambient"]["r"].asFloat();
		ambient.g = currentLight["ambient"]["g"].asFloat();
		ambient.b = currentLight["ambient"]["b"].asFloat();

		diffuse.r = currentLight["diffuse"]["r"].asFloat();
		diffuse.g = currentLight["diffuse"]["g"].asFloat();
		diffuse.b = currentLight["diffuse"]["b"].asFloat();

		specular.r = currentLight["specular"]["r"].asFloat();
		specular.g = currentLight["specular"]["g"].asFloat();
		specular.b = currentLight["specular"]["b"].asFloat();

		// position
		

		// direction
		direction.x = currentLight["direction"]["x"].asFloat();
		direction.y = currentLight["direction"]["y"].asFloat();
		direction.z = currentLight["direction"]["z"].asFloat();

		// set the values into the light
		l.setAmbient(ambient);
		l.setDiffuse(diffuse);
		l.setSpecular(specular);
		l.setDirection(direction);

		sceneLights.push_back(l);
	}
	newScene.setLights(sceneLights);

	newScene.setDecoration(vEntityDecorations);

	return newScene;
}

vector<Button> SceneCreator::createButtons(string file) {
	string buttonsString = FileReader::LoadStringFromFile(file);
	Json::Reader reader;
	Json::Value json;

	reader.parse(buttonsString, json);
	int size = json["size"].asInt();
	OBJ object = Geometry::LoadModelFromFile(json["object"].asString());
	vector<Button> vectorButtons;
	for (int i = 0; i < size; i++) {
		string currentButton = "button" + std::to_string(i);
		Button newButton;
		newButton.setOBJ(object);

		Material mat;
		mat.ambient = glm::vec3(1, 1, 1);
		mat.diffuse = glm::vec3(1, 1, 1);
		mat.specular = glm::vec3(1, 1, 1);

		mat.textureMap = TextureManager::Instance().getTextureID(json[currentButton]["texture_on"].asString());
		GameObject buttonObject;
		buttonObject._translate.x = json[currentButton]["position"]["x"].asInt();
		buttonObject._translate.y = json[currentButton]["position"]["y"].asInt();
		buttonObject._translate.z = json[currentButton]["position"]["z"].asInt();
		
		buttonObject._scale = glm::vec3(1, 1, 1);
		buttonObject._angle = 180;
		buttonObject._rotation = glm::vec3(0,0,1);
		
		newButton.setGameObject(buttonObject);
		newButton.setMaterial(mat);
		newButton.setTextureOff(TextureManager::Instance().getTextureID(json[currentButton]["texture_off"].asString()));
		vectorButtons.push_back(newButton);
	}

	return vectorButtons;
}