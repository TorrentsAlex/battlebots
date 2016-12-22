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

	// Terrain and skybox
	populateTerrain(&newScene, json);

	populateDecoration(&newScene, json);

	// Lights
	vector<Light> sceneLights = populateLights(json["lights"]);
	newScene.setLights(sceneLights);

}

void SceneCreator::createCharacters(string file, Character& ch1, Character& ch2, Character& ch3, Character& ch4) {
	
	/*
			IMPORTANT!!!!

			see these page fot anti tunneling
			http://bulletphysics.org/mediawiki-1.5.8/index.php/Anti_tunneling_by_Motion_Clamping
	*/
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

	gameObject.angle = 0;
	gameObject.rotation = glm::vec3(0,0,1);
	gameObject.scale = glm::vec3(0.8, 0.8, 0.8);

	gameObject.translate.x = json["character0"]["position"]["x"].asFloat();
	gameObject.translate.y = json["character0"]["position"]["y"].asFloat();
	gameObject.translate.z = json["character0"]["position"]["z"].asFloat();
	ch1.setGameObject(gameObject);

	gameObject.translate.x = json["character1"]["position"]["x"].asFloat();
	gameObject.translate.y = json["character1"]["position"]["y"].asFloat();
	gameObject.translate.z = json["character1"]["position"]["z"].asFloat();
	ch2.setGameObject(gameObject);

	gameObject.translate.x = json["character2"]["position"]["x"].asFloat();
	gameObject.translate.y = json["character2"]["position"]["y"].asFloat();
	gameObject.translate.z = json["character2"]["position"]["z"].asFloat();
	ch3.setGameObject(gameObject);

	gameObject.translate.x = json["character3"]["position"]["x"].asFloat();
	gameObject.translate.y = json["character3"]["position"]["y"].asFloat();
	gameObject.translate.z = json["character3"]["position"]["z"].asFloat();
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
	//GLuint specularMap = TextureManager::Instance().getTextureID("../battlebots/Game/resources/images/back_green.png");

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
		buttonObject.translate.x = json[currentButton]["position"]["x"].asFloat();
		buttonObject.translate.y = json[currentButton]["position"]["y"].asFloat();
		buttonObject.translate.z = json[currentButton]["position"]["z"].asFloat();
		
		Json::Value scaleJson = json[currentButton].get("scale", NULL);
		if (scaleJson != NULL) {
			buttonObject.scale.x = scaleJson["x"].asFloat();
			buttonObject.scale.y = scaleJson["y"].asFloat();
			buttonObject.scale.z = scaleJson["z"].asFloat();
		} else {
			buttonObject.scale = glm::vec3(1, 1, 1);
		}
		
		buttonObject.angle = 0;
		buttonObject.rotation = glm::vec3(0,0,0);
		
		newButton.setName(json[currentButton]["name"].asString());
		newButton.setGameObject(buttonObject);
		newButton.setMaterial(mat);
		newButton.setTextureOff(TextureManager::Instance().getTextureID(json[currentButton]["texture_on"].asString()));

		//newButton.setSpecularMap(specularMap);

		vectorButtons.push_back(newButton);
	}

	return vectorButtons;
}



/**
	Create a vector of lights with the json Scene and return
*/

vector<Light> SceneCreator::populateLights(Json::Value jsonLights) {
	Json::Reader reader;
	vector<Light> sceneLights;
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
	return sceneLights;
}

void SceneCreator::createRigidBodyForDecoration(Scene * scene, Entity* entity) {


}

void SceneCreator::populateDecoration(Scene * scene, Json::Value decoration) {

	cout << "decoration..." << endl;
	Json::Value jsonDecoration = decoration["decoration"];
	// Decoration
	vector<Entity> vEntityDecorations;
	for (int i = 0; i < jsonDecoration.size(); i++) {
		Json::Value currentDecoration = jsonDecoration[i];
		OBJ objDecoration = Geometry::LoadModelFromFile(currentDecoration["object"].asString());
		GLuint textureDecoration = TextureManager::Instance().getTextureID(currentDecoration["texture"].asString());

		string gameElements = currentDecoration["elements"].asString();
		string textureSpecularString = currentDecoration["texture_specular"].asString();

		Entity* e = new Entity();
		e->setOBJ(objDecoration);
		e->setMaterial(metalMaterial);
		e->setTextureId(textureDecoration);
		DecorObjects d;
		d.e = e;
		

		//set specular material
		if (textureSpecularString.compare("") != 0) {
			GLuint specular = TextureManager::Instance().getTextureID(textureSpecularString);
			e->setTextureSpecular(specular);
		}

		// Theres nothin into elements
		if (gameElements.compare("") == 0) {
			GameObject gameObject;
			gameObject.translate = glm::vec3(currentDecoration["position"]["x"].asFloat(), currentDecoration["position"]["y"].asFloat(), currentDecoration["position"]["z"].asFloat());;

			gameObject.scale = glm::vec3(1, 1, 1);
			gameObject.angle = 0;

			std::vector<GameObject> gameObjects;
			gameObjects.push_back(gameObject);
			d.g.push_back(gameObject);

			scene->listObjects.push_back(d);

		} else { // There are more than 1 element
			d.g = Geometry::LoadGameElements(gameElements);
			glm::vec3 volume = e->getCollisionVolume();
			
			btScalar mass = currentDecoration["mass"].asFloat();
			cout << "mass " << mass << endl;
 			bool isDynamic = (mass != 0.f);

			btVector3 localInertia(0, 0, 0);
			btTransform objectOrigin;
			for (int i = 0; i < d.g.size();i++) {
				btCollisionObject* collObject = new btCollisionObject();
				// Box shape to collisionObject
				btCollisionShape* colShape = new btBoxShape(btVector3(volume.x, volume.y, volume.z));
							
				collObject->setCollisionShape(colShape);
				// Calculate inertia
				if (isDynamic) colShape->calculateLocalInertia(mass, localInertia);

				objectOrigin.setOrigin(btVector3(d.g.at(i).translate.x, d.g.at(i).translate.y, d.g.at(i).translate.z + volume.z/2.0f));
				collObject->setWorldTransform(objectOrigin);

				//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
				btDefaultMotionState* myMotionState1 = new btDefaultMotionState(objectOrigin);
				btRigidBody::btRigidBodyConstructionInfo rbInfo1(mass, myMotionState1, colShape, localInertia);
				btRigidBody* body = new btRigidBody(rbInfo1);

				scene->addBodyToDynamicWorld(body); //bt
				d.g.at(i).collisionObject = body; //btRigidBody
			}
			scene->listObjects.push_back(d);
		}
	}
}

void SceneCreator::populateTerrain(Scene * scene, Json::Value terrain) {

	// SkyBox
	OBJ objSky = Geometry::LoadModelFromFile(terrain["sky"]["object"].asString());
	GLuint textureSky = TextureManager::Instance().getTextureID(terrain["sky"]["texture"].asString());
	btTransform btTSky;
	btTSky.setIdentity();
	btTSky.setOrigin(btVector3(0, 0, 0));
	btCollisionShape* skyShape = new btBoxShape(btVector3(0,0,0));
	btScalar skymass(0.);
	btVector3 skylocalInertia(0, 0, 0);

	// Create terrain collision object 
	btDefaultMotionState* myMotionStatesky = new btDefaultMotionState(btTSky);
	btRigidBody::btRigidBodyConstructionInfo rbInfosky(skymass, myMotionStatesky, skyShape, skylocalInertia);
	btRigidBody* skyBody = new btRigidBody(rbInfosky);


	scene->setSkyBox(objSky, textureSky, skyBody);
	scene->addBodyToDynamicWorld(skyBody);


	cout << "terrain..." << endl;
	// Terrain
	OBJ objTerrain = Geometry::LoadModelFromFile(terrain["terrain"]["object"].asString());
	GLuint textureTerrain = TextureManager::Instance().getTextureID(terrain["terrain"]["texture"].asString());
	// Terrain material
	
	// Set physics for terrain
	glm::vec3 terrainVolume = scene->getTerrain().getCollisionVolume();

	btTransform btTGround;
	btTGround.setIdentity();
	btTGround.setOrigin(btVector3(0, 0, 0));
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(terrainVolume.x), btScalar(terrainVolume.y), btScalar(10.0f)));
	
	
	//collisionShapes.push_back(groundShape);
	btScalar mass(0.);
	btVector3 localInertia(0, 0, 0);
	
	// Create terrain collision object 
	btDefaultMotionState* myMotionState = new btDefaultMotionState(btTGround);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	
	scene->addBodyToDynamicWorld(body);
	scene->setTerrain(objTerrain, textureTerrain, metalMaterial, body);


}
