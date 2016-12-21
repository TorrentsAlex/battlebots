#pragma once
#include "Entity.h"

const float TOTAL_BARREL_BEER = 1.0f;
const float PERCENTAGE_TO_SUBSTRACT = 25; // %

class BarrelBeer : public Entity {
private:

	float bTotalBeerInBarrel = 0.5f;
	
	float bRadiousToInteract = 1.5f;

public:
	BarrelBeer();
	~BarrelBeer();

	float stealBeer();
	void fillBarrel(float beer);

};

