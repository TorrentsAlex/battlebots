#include "BarrelBeer.h"



BarrelBeer::BarrelBeer() {
}


BarrelBeer::~BarrelBeer() {
}

float BarrelBeer::stealBeer() {
	float substract = TOTAL_BARREL_BEER * 100 / PERCENTAGE_TO_SUBSTRACT;
	bTotalBeerInBarrel -= substract;
	return substract;
}

void BarrelBeer::fillBarrel(float beer) {
	bTotalBeerInBarrel += beer;
}
