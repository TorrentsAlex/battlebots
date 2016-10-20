#include "Character.h"

#include "GamePad.h"

Character::Character() {
	rGamePad = new GamePad();
	vectorForward = glm::vec3(1, 0, 0);
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
	switch (currentState) {
	case DASHING:
		//calcular tiempos y aplicar cooldown a la llamada.

		break;

	case WALKING:
		// Reducir drunkennes por tiempo.

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
	currentState = WALKING;

	// Invert Y axis
	// Get a value between 0 and 1
	axis.x /= 32767;
	axis.y /= 32767;

	eGameObject._translate.x += axis.x * velocity;
	eGameObject._translate.y += axis.y * velocity;
}

void Character::rotation(glm::vec2 axis) {
	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);
	glm::vec2 forwardRotated = glm::rotate(glm::vec2(1, 0), (float)angle);
	vectorForward.x = forwardRotated.x;
	vectorForward.y = forwardRotated.y;
	eGameObject._angle = angle;
	cout << " angle: " << angle << endl;
}

void Character::jump() {
	currentState = JUMPING;
	cout << "jump " << vectorForward.x << "/" << vectorForward.y << endl;
	//eGameObject._translate.z += jumpPower;
	
}

void Character::dash() {

	if (currentState == DASHING) {
		return;
	}

	// REVISAR CALCULO Y IMPLEMENTAR BIEN
	glm::vec2 finalPosition;
	finalPosition.x = (eGameObject._translate.x + velocity * dashTime + ((1 / 2)*dashAcceleration*(dashTime*dashTime)));
	finalPosition.y = (eGameObject._translate.y + velocity * dashTime + ((1 / 2)*dashAcceleration*(dashTime*dashTime)));
	
	currentState = DASHING;

	eGameObject._translate.x += vectorForward.x * velocity * dashAcceleration*dashAcceleration;
	eGameObject._translate.y += vectorForward.y * velocity * dashAcceleration*dashAcceleration;
	
}
void Character::shoot() {

}

void Character::refill() {
	currentState = REFILL;

}

void Character::drink() {
	currentState = DRINKING;

}

void Character::pointGun(float x, float y) {

}