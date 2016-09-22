#pragma once
#include <iostream>
#include <glm\glm.hpp>
#include <time.h>

#include "Entity.h"

#define GRAVITY -0.00981
#define MAX_PARTICLES 500

struct Particle {
	float life;
	float velocity;
	GameObject particleObject;
	float weight;
};

class ParticleSystem: public Entity {
private:
	std::vector<Particle> pParticles;
	int currentParticle = 0;
	
	float initTime;
	float currentTime;

	glm::vec3 pCenterOfRain;
	glm::vec2 pWind;
	float pMaxDistance = 10;

public:
	ParticleSystem();
	~ParticleSystem();

	void initParticleSystem();
	void initParticleSystem(glm::vec3 centerOfRain);

	void startRain();
	void moreXWind();
	void lessXWind();
	void moreYWind();
	void lessYWind();

	GameObject getGameObject();
	int getSize();
	void nextParticle();

	void update();
	void updateCenterOfRain(glm::vec3 centerOfRain);
	//void physics();
};

