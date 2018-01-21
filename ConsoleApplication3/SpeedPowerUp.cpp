#include "SpeedPowerUp.h"
#include <iostream>


/*
	Speed Power Up constructor sets the texture to be a lightining bolt and also sets the speed gained and time to last based on the parameters
*/
SpeedPowerUp::SpeedPowerUp(int speed, int time)
{
	speedTexture.loadFromFile("lightning-bolt.png");
	setTexture(speedTexture);
	speedGained = speed;
	timeLasting = time;
}
/*
	Returns the speed of the power up
*/
int SpeedPowerUp::getSpeed()
{
	return speedGained;
}
/*
	Returns the time remaining of the power up
*/
int SpeedPowerUp::getTimeRemaining()
{
	return timeLasting;
}
/*
	Sets the speed of the power up, int taken as a parameter
*/
void SpeedPowerUp::setSpeed(int setSpeed)
{
	speedGained = setSpeed;
}
/*
	Sets the time remaining of the power up, int taken as a parameter
*/
void SpeedPowerUp::setTimeRemaining(int setTimeLeft)
{
	timeLasting = setTimeLeft;
}