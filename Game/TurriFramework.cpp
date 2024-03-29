#include "TurriFramework.h"


void TurriFramework::init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS) {
	tFPS.init(enableLimiterFPS, maxFPS, printFPS);
	// Up SDL window
	tWindow.create(name, screenWidth, screenheight, 0);

	// init input manager
	InputManager::Instance().init();

	// Up shaders
	tOpenGL.initializeShaders();

	// Up Camera
	tCamera.initializeZBuffer(glm::vec2(screenWidth, screenheight)); 

	tCamera.setPerspectiveCamera();
	tCamera.setViewMatrix();
	running = true;

	//  init Cube for debug collisions
	unitCube = Geometry::LoadModelFromFile("./resources/objects/cube.obj");
	cubeMaterial.textureMap = TextureManager::Instance().getTextureID("../battlebots/Game/resources/images/back_green.png");
	cubeMaterial.ambient = glm::vec3(0.25, 0.20725, 0.20725);
	cubeMaterial.diffuse = glm::vec3(0.25, 0.20725, 0.20725);
	cubeMaterial.specular = glm::vec3(0.25, 0.20725, 0.20725);
	cubeMaterial.shininess = 4;
}

bool TurriFramework::isRunning() {
	return running;
}

void TurriFramework::startSync() {
	tFPS.startSynchronization();
}

void TurriFramework::endSync() {
	tFPS.forceSynchronization();
}

void TurriFramework::update() {
	// Update Inputs
	//InputManager::Instance().update();
}

// Render methods
void TurriFramework::startRender() {
	tOpenGL.start();
	tOpenGL.setFillOrWireframe(POLYGONMODE::FILL);
}

void TurriFramework::stopRender() {
	
	tOpenGL.sceneWithLights(false);

	tOpenGL.end();
	tWindow.swapBuffer();
}

void TurriFramework::clearMaps() {
	tOpenGL.unbindMaps();
}

void TurriFramework::renderLights(vector<Light> lights) {
	tOpenGL.sceneWithLights(true);
	tOpenGL.sendLight(lights);
}

void TurriFramework::disableLights() {
	tOpenGL.sceneWithLights(false);
}

void TurriFramework::renderCube(GameObject* gameObject) {
	tOpenGL.setFillOrWireframe(POLYGONMODE::WIREFRAME);

	tOpenGL.sendObject(unitCube.mesh, *gameObject, unitCube.numVertices);
}

void TurriFramework::renderCubeAt(GameObject* entityObject, glm::vec3 volume) {

	GameObject* gameObject = entityObject;
	gameObject->scale = glm::vec3(volume.x, volume.y, volume.z);

	tOpenGL.sendMaterial(cubeMaterial);
	renderCube(gameObject);
	tOpenGL.unbindMaps();
}

void TurriFramework::renderCubeAt(Entity* entity) {

	btVector3 transform = entity->getCollisionObject().getWorldTransform().getOrigin();
	float x = transform.getX();
	float y = transform.getY();
	float z = transform.getZ();
	
	glm::vec3 scale = entity->getCollisionVolume();
	
	GameObject gameObject;
	gameObject.translate = glm::vec3(x, y, z);
	gameObject.angle = 0;
	gameObject.scale = glm::vec3(scale.x, scale.y, scale.z);

	tOpenGL.sendMaterial(cubeMaterial);
	renderCube(&gameObject);
	tOpenGL.unbindMaps();
}

void TurriFramework::renderEntity(Entity* entity) {
	
	tOpenGL.sendMaterial(entity->getMaterial());
	tOpenGL.sendObject(entity->getMesh(), entity->getGameObject(), entity->getNumVertices());
	clearMaps();
}

void TurriFramework::renderScene(Scene* scene) {
	// Terrain
	Entity terrain = scene->getTerrain();
	tOpenGL.sendMaterial(terrain.getMaterial());
	tOpenGL.sendObject(terrain.getMesh(), terrain.getGameObject(), terrain.getNumVertices());

	clearMaps();

	for (DecorObjects decor : scene->listObjects) {
		tOpenGL.sendMaterial(decor.e->getMaterial());

		for (GameObject gameObject : decor.g) {

			tOpenGL.sendObject(decor.e->getMesh(), gameObject, decor.e->getNumVertices());

		}
		clearMaps();
	}


}

// send Camera values
void TurriFramework::renderCamera() {
	tOpenGL.sendViewerPosition(tCamera.getPosition());

	tOpenGL.sendViewTransformationMatrix(tCamera.getViewMatrix(), tCamera.getProjectionCamera());
}

void TurriFramework::setScreenSize(int widthScreen, int heightScreen) {
	glm::vec2 newResolution = glm::vec2(widthScreen, heightScreen);

	tWindow.setScreenSize(newResolution.x, newResolution.y);
	tCamera.initializeZBuffer(newResolution);

	tCamera.setViewMatrix();
}

void TurriFramework::addFlagscreen(unsigned int currentFlag) {
	
	if (currentFlag == (int)WindowFlags::FULLSCREEN) {
		tWindow.setFullScreen();
		tCamera.initializeZBuffer(tWindow.getNativeResolution());

		tCamera.setViewMatrix();
	}
	if (currentFlag == (int)WindowFlags::BORDERLESS) {
		tWindow.setWindowedScreen();
	}
}

// Camera 
void TurriFramework::setCameraPosition(glm::vec3 position) {
	tCamera.setCameraPosition(position);
}

void TurriFramework::setCameraLookAt(glm::vec3 lookAt) {
	tCamera.setCameraFront(lookAt);
}

glm::vec3 TurriFramework::getCameraPosition() {
	return tCamera.getPosition();
}

void TurriFramework::moveCameraWithKeyboard() {
	glm::vec3 cameraPos = tCamera.getPosition();
	// Show fps
	if (InputManager::Instance().isKeyDown(SDLK_f)) {
		tFPS.showFPS();
	}

	if (InputManager::Instance().isKeyDown(SDLK_q)) {
		cameraPos.y += 1;
	}
	if (InputManager::Instance().isKeyDown(SDLK_e)) {
		cameraPos.y -= 1;
	}
	if (InputManager::Instance().isKeyDown(SDLK_w)) {
		cameraPos.z += 1;
	}
	if (InputManager::Instance().isKeyDown(SDLK_s)) {
		cameraPos.z -= 1;
	}
	if (InputManager::Instance().isKeyDown(SDLK_a)) {
		cameraPos.x -= 1;
	}
	if (InputManager::Instance().isKeyDown(SDLK_d)) {
		cameraPos.x += 1;
	}
	tCamera.setCameraPosition(cameraPos);
}

// Input methods

// Finish the game loop
void TurriFramework::quit() {
	running = false;
}



