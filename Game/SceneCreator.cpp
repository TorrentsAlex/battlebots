#include "SceneCreator.h"


void SceneCreator::createScene(string file, Scene& newScene) {
	cout << "creating scene" << endl;
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
	Json::Value jsonDecoration = json["decoration"];
	// Decoration
	vector<Entity> vEntityDecorations;
	for (int i = 0; i < jsonDecoration.size(); i++) {
		Json::Value currentDecoration = jsonDecoration[i];
		OBJ objDecoration = Geometry::LoadModelFromFile(currentDecoration["object"].asString());
		GLuint textureDecoration = TextureManager::Instance().getTextureID(currentDecoration["texture"].asString());

		string gameElements = currentDecoration["elements"].asString();
		string textureSpecularString = currentDecoration["texture_specular"].asString();
		Entity entity;
		entity.setOBJ(objDecoration);
		entity.setMaterial(terrainMaterial);
		entity.setTextureId(textureDecoration);

		//set specular material
		if (textureSpecularString.compare("") != 0) {
			GLuint specular = TextureManager::Instance().getTextureID(textureSpecularString);
			entity.setTextureSpecular(specular);
		}
		

		// Theres nothin into elements
		if (gameElements.compare("") == 0) {
			GameObject gameObject;
			gameObject._translate = glm::vec3(currentDecoration["position"]["x"].asFloat(), currentDecoration["position"]["y"].asFloat(), currentDecoration["position"]["z"].asFloat());;

			gameObject._scale = glm::vec3(1, 1, 1);
			gameObject._angle = 0;
			entity.setGameObject(gameObject);
			vEntityDecorations.push_back(entity);

		} else {
			vector<GameObject> vectorDecoration = Geometry::LoadGameElements(gameElements);
			for (GameObject gODecoration : vectorDecoration) {
				entity.setGameObject(gODecoration);

				vEntityDecorations.push_back(entity);
			}
		}
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
		position.x = currentLight["position"]["x"].asFloat();
		position.y = currentLight["position"]["y"].asFloat();
		position.z = currentLight["position"]["z"].asFloat();
		
		// direction
		direction.x = currentLight["direction"]["x"].asFloat();
		direction.y = currentLight["direction"]["y"].asFloat();
		direction.z = currentLight["direction"]["z"].asFloat();
		
		// type
		string type = currentLight["type"].asString();
		l.setType(type);
		// if the light is a pointlight
		if (type.compare("point") == 0) {
			float constant = currentLight["constant"].asFloat();
			float linear = currentLight["linear"].asFloat();
			float quadratic = currentLight["quadratic"].asFloat();
			l.setConstant(constant);
			l.setLinear(linear);
			l.setQuadratic(quadratic);
		}
		//power 
		float power = currentLight["power"].asFloat();
		l.setPower(power);

		// set the values into the light
		l.setAmbient(ambient);
		l.setDiffuse(diffuse);
		l.setSpecular(specular);
		l.setDirection(direction);
		l.setPosition(position);

		sceneLights.push_back(l);
	}
	newScene.setLights(sceneLights);

	newScene.setDecoration(vEntityDecorations);
}

void SceneCreator::createCharacters(string file, Character& ch1, Character& ch2, Character& ch3, Character& ch4) {
	cout << "creating characters" << endl;
	Scene newScene;
	Json::Reader reader;
	Json::Value json;

	// Load File and save it into string
	string jsonString = FileReader::LoadStringFromFile(file);
	// Parse the string into json
	reader.parse(jsonString, json);
	
	// Load MODEL
	OBJ object = Geometry::LoadModelFromFile(json["character0"]["object"].asString());
	ch1.setOBJ(object);
	ch2.setOBJ(object);
	ch3.setOBJ(object);
	ch4.setOBJ(object);

	// Load position
	GameObject gameObject;

	gameObject._angle = 0;
	gameObject._rotation = glm::vec3(0,0,1);
	gameObject._scale = glm::vec3(0.8, 0.8, 0.8);

	gameObject._translate.x = json["character0"]["position"]["x"].asFloat();
	gameObject._translate.y = json["character0"]["position"]["y"].asFloat();
	gameObject._translate.z = json["character0"]["position"]["z"].asFloat();
	ch1.setGameObject(gameObject);

	gameObject._translate.x = json["character1"]["position"]["x"].asFloat();
	gameObject._translate.y = json["character1"]["position"]["y"].asFloat();
	gameObject._translate.z = json["character1"]["position"]["z"].asFloat();
	ch2.setGameObject(gameObject);

	gameObject._translate.x = json["character2"]["position"]["x"].asFloat();
	gameObject._translate.y = json["character2"]["position"]["y"].asFloat();
	gameObject._translate.z = json["character2"]["position"]["z"].asFloat();
	ch3.setGameObject(gameObject);

	gameObject._translate.x = json["character3"]["position"]["x"].asFloat();
	gameObject._translate.y = json["character3"]["position"]["y"].asFloat();
	gameObject._translate.z = json["character3"]["position"]["z"].asFloat();
	ch4.setGameObject(gameObject);

	// Material
	Material mat;
	mat.ambient = glm::vec3(0.25, 0.20725, 0.20725);
	mat.diffuse = glm::vec3(0.25, 0.20725, 0.20725);
	mat.specular = glm::vec3(0.25, 0.20725, 0.20725);
	mat.shininess = 32;
	//mat.specularMap = TextureManager::Instance().getTextureID("./resources/images/dwarfsg.png");

	ch1.setMaterial(mat);
	ch2.setMaterial(mat);
	ch3.setMaterial(mat);
	ch4.setMaterial(mat);

	// Texture
	ch1.setTextureId(TextureManager::Instance().getTextureID(json["character0"]["texture"].asString()));
	ch2.setTextureId(TextureManager::Instance().getTextureID(json["character1"]["texture"].asString()));
	ch3.setTextureId(TextureManager::Instance().getTextureID(json["character2"]["texture"].asString()));
	ch4.setTextureId(TextureManager::Instance().getTextureID(json["character3"]["texture"].asString()));
}

vector<Button> SceneCreator::createButtons(string file) {
	string buttonsString = FileReader::LoadStringFromFile(file);
	Json::Reader reader;
	Json::Value json;

	reader.parse(buttonsString, json);
	int size = json["size"].asInt();
	OBJ object = Geometry::LoadModelFromFile(json["object"].asString());
	vector<Button> vectorButtons;
	GLuint specularMap = TextureManager::Instance().getTextureID("./resources/images/back_green.png");

	for (int i = 0; i < size; i++) {
		string currentButton = "button" + std::to_string(i);
		Button newButton;
		newButton.setOBJ(object);

		Material mat;
		mat.ambient = glm::vec3(0.25, 0.20725, 0.20725);
		mat.diffuse = glm::vec3(0.25, 0.20725, 0.20725);
		mat.specular = glm::vec3(0.25, 0.20725, 0.20725);
		mat.shininess = 32;

		string texture = json[currentButton]["texture_on"].asString();
		mat.textureMap = TextureManager::Instance().getTextureID(texture);
		GameObject buttonObject;
		buttonObject._translate.x = json[currentButton]["position"]["x"].asInt();
		buttonObject._translate.y = json[currentButton]["position"]["y"].asInt();
		buttonObject._translate.z = json[currentButton]["position"]["z"].asInt();
		
		Json::Value scaleJson = json[currentButton].get("scale", NULL);
		if (scaleJson != NULL) {
			buttonObject._scale.x = scaleJson["x"].asFloat();
			buttonObject._scale.y = scaleJson["y"].asFloat();
			buttonObject._scale.z = scaleJson["z"].asFloat();
		} else {
			buttonObject._scale = glm::vec3(1, 1, 1);
		}
		
		buttonObject._angle = 0;
		buttonObject._rotation = glm::vec3(0,0,0);
		
		newButton.setName(json[currentButton]["name"].asString());
		newButton.setGameObject(buttonObject);
		newButton.setMaterial(mat);
		newButton.setTextureOff(TextureManager::Instance().getTextureID(json[currentButton]["texture_on"].asString()));

		newButton.setSpecularMap(specularMap);

		vectorButtons.push_back(newButton);
	}

	return vectorButtons;
}