#include "Character.h"

#include "GamePad.h"

Character::Character():
	maxDashVelocity(6) {
	rGamePad = new GamePad();

	vectorForward = glm::vec3(0, 1, 0);
	currentState = STATE::IDLE;
}

Character::~Character() {
	if (rGamePad) {
		delete rGamePad;
	}
}

void Character::clean() {
	SDL_GameControllerClose(rGamePad->gameController);
	rGamePad->clean();
}

void Character::update() {
	btTransform transform = collisionObject->getWorldTransform();

	btVector3 origin = transform.getOrigin();
	float x = origin.getX();
	float y = origin.getY();

	switch (currentState) {
	case IDLE:
		currentVelocity = 0;

		break;
	case DASHING:
		//calcular tiempos y aplicar cooldown a la llamada.
		currentVelocity += dashAcceleration;

		eGameObject._translate.x += dashForward.x * currentVelocity; 
		eGameObject._translate.y += dashForward.y * currentVelocity; 

		if (currentVelocity >= maxDashVelocity) {
			currentState = STATE::IDLE; 
			currentVelocity = 0;
			// Cooldown for DASH
			firstTick = SDL_GetTicks();
		}
		break;
	case WALKING:
		// Reducir drunkennes por tiempo.
		if (currentVelocity <= maxVelocity) {
			currentVelocity += acceleration;
		}
		x += vectorForward.x * currentVelocity;
		y += vectorForward.y * currentVelocity;

		transform.setOrigin(btVector3(x, y, origin.getZ()));
		collisionObject->setWorldTransform(transform);
		currentState = STATE::IDLE;

		break;

	case JUMPING:
		// NO tiene cooldown, vigilar con la reduccion de drunkennes (OPINION: x2/x3?, para evitar el abuso de este estado)

		break;

	case DRINKING:
		// Reducir nivel de remainingBeer y aumentar en misma medida el drunkennes. Tener en cuenta el tiempo que esta pulsado
		// para reducir segun el tiempo.

		break;

	case REFILL:
		// Aumentar nivel de remainingBeer por tiempo que esta realizando esta acción, hasta el nivel maximo (0 E / 1 F)

		break;

	case STUNNED:
		// Reducir el nivel de RemainingBeer a la mitad de la que se tiene en el momento (TEST)
		// Bloquear al personaje en este estado durante X segundos. (Controlador por stunTime.

		break;
	}

	//cout << currentVelocity << endl;
}

void Character::input() {

}

void Character::setGamePad(GamePad& gamePad) {
	*rGamePad = gamePad;
}

GamePad* Character::getGamePad() {
	return rGamePad;
}

void Character::movement(glm::vec2 axis) {
	if (currentState == STATE::DASHING ||
		currentState == STATE::DRINKING ||
		currentState == STATE::STUNNED) {
		return;
	}
	currentState = STATE::WALKING;
	// Invert Y axis
	// Get a value between 0 and 1
	axis.x /= 32767;
	axis.y /= 32767; 

	// Rotate
	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);
	glm::vec2 forwardRotated = glm::rotate(glm::vec2(1, 0), (float)angle);
	vectorForward.x = forwardRotated.x;
	vectorForward.y = forwardRotated.y;
	eGameObject._angle = angle;
	//cout << " angle: " << angle << endl;
}

void Character::rotation(glm::vec2 axis) {
}

void Character::jump() {

	currentState = JUMPING;
	cout << "jump " << vectorForward.x << "/" << vectorForward.y << endl;
	//eGameObject._translate.z += jumpPower;
	
}

void Character::dash() {
	float currentTicks = SDL_GetTicks();
	if (currentState == STATE::DASHING || 
		(currentTicks <= firstTick + dashCooldown)) {
	
	} else {
		firstTick = 0;

		currentState = DASHING;
		dashForward = vectorForward;
	}
}

void Character::shoot() {
	Json::Reader reader;

	string jsonString = FileReader::LoadStringFromFile("./resources/scenes/character_values.json");
	Json::Value jsonValues;

	reader.parse(jsonString, jsonValues);
	acceleration = jsonValues["walking"]["acceleration"].asFloat();
	maxVelocity = jsonValues["walking"]["max_velocity"].asFloat();

	dashAcceleration = jsonValues["dash"]["acceleration"].asFloat();
	maxDashVelocity = jsonValues["dash"]["max_velocity"].asFloat();

	dashCooldown = jsonValues["dash_cooldown"].asFloat();

	cout << "Character values readed and saved!!" << endl;
}

void Character::refill() {
	currentState = REFILL;

}

void Character::drink() {
	currentState = DRINKING;

}

void Character::pointGun(float x, float y) {

}