#include "HealthPowerUp.h"
#include <iostream>
/*
	Creates a health power up, sets the health gained to 25 and sets it to be a heart texture
*/
HealthPowerUp::HealthPowerUp()
{
	heartsTexture.loadFromFile("heartPowerUp.png");
	setTexture(heartsTexture);
	healthGained = 25;
}
/*
	Return the amount of health regained by the power up
*/
int HealthPowerUp::getHealthGained()
{
	return healthGained;
}