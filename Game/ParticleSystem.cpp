#include "ParticleSystem.h"



ParticleSystem::ParticleSystem():
	pWind(0, 0) {
}


ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::initParticleSystem() {
}

void ParticleSystem::initParticleSystem(glm::vec3 centerOfRain) {

	std::cout << "Init particles" << std::endl;
	for (int i = 0; i < MAX_PARTICLES; i++) {
		Particle particle;
		GameObject pObject;
		pObject._angle = 0;
		pObject._rotation = glm::vec3(0,0,0);
		pObject._scale = glm::vec3(0.05f, 0.05f, 0.05f);
		glm::vec3 position;
		position.x = centerOfRain.x + rand() % 21 + rand() % 9 + 1 / 10 - pMaxDistance;
		position.y = centerOfRain.y + rand() % 21 + rand() % 9 + 1 / 10 - pMaxDistance;
		position.z = rand() % 10 + 5 + rand() % 9 + 1/10;

		pObject._translate = position;

		particle.particleObject = pObject;
		particle.life = rand() % 5 + 3;
		particle.weight = (rand() % 5 + 1) / 20000;
		particle.velocity = (rand() % 9 + 5) / 100;

		pParticles.push_back(particle);
	}
}

void ParticleSystem::startRain() {
	time_t timer;
	/*struct tm y2k = { 0 };
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	time(&timer);
	*/
	initTime = ((float)clock() / CLOCKS_PER_SEC);
}

void ParticleSystem::update() {
	float newVelocity;

	currentTime = ((float)clock() / CLOCKS_PER_SEC) - initTime;

	for (int i = 0; i < pParticles.size(); i++) {

		// dropping particle
		pParticles.at(i).velocity += GRAVITY;
		pParticles.at(i).particleObject._translate.z +=	pParticles.at(i).velocity;
		
		// wind effect
		pParticles.at(i).particleObject._translate.x += pWind.x;
		pParticles.at(i).particleObject._translate.y += pWind.y;

		// Check height position
		if (pParticles.at(i).particleObject._translate.z <= 0) {
			// reset z and velocity
			pParticles.at(i).particleObject._translate.z = rand() % 10 + 5;
			pParticles.at(i).velocity = (rand() % 9 + 5) / 100;

			// reset x and y checking with the radius
			float xDistance = pParticles.at(i).particleObject._translate.x - pCenterOfRain.x;
			float yDistance = pParticles.at(i).particleObject._translate.y - pCenterOfRain.y;
			// Too slow :(
			if (xDistance >= pMaxDistance ||
				xDistance <= pMaxDistance) {
				pParticles.at(i).particleObject._translate.x = rand() % 21 - pMaxDistance + pCenterOfRain.x;
			}
			if (yDistance >= pMaxDistance ||
				yDistance <= pMaxDistance) {

				pParticles.at(i).particleObject._translate.y = rand() % 21 - pMaxDistance + pCenterOfRain.y;
			}
		}
		// check life
	}
}


void ParticleSystem::updateCenterOfRain(glm::vec3 centerOfRain) {
	pCenterOfRain = centerOfRain;
}

// Getters
GameObject ParticleSystem::getGameObject() {
	return pParticles.at(currentParticle).particleObject;
}

int ParticleSystem::getSize() {
	return MAX_PARTICLES;        
}

void ParticleSystem::nextParticle() {
	currentParticle++;
	if (currentParticle >= MAX_PARTICLES) {
		currentParticle = 0;
	}
}

// Wind methods
void ParticleSystem::moreXWind() {
	if (pWind.x <= 0.75) {
		pWind.x += 0.25;
	}
}

void ParticleSystem::lessXWind() {
	if (pWind.x >= -0.75) {
		pWind.x -= 0.25;
	}
}

void ParticleSystem::moreYWind() {
	if (pWind.y <= 0.75) {
		pWind.y += 0.25;
	}
}

void ParticleSystem::lessYWind() {
	if (pWind.y >= -0.75) {
		pWind.y -= 0.25;
	}
}