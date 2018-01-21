#include "DamageDonePowerUp.h"
#include <iostream>

DamageDonePowerUp::DamageDonePowerUp(int damageGainedInput, int time)
{
	powerUpTexture.loadFromFile("damageIncrease.png");
	setTexture(powerUpTexture);
	damageGained = damageGainedInput;
	timeLasting = time;
}
int DamageDonePowerUp::getDamageGained()
{
	return damageGained;
}
int DamageDonePowerUp::getTimeRemaining()
{
	return timeLasting;
}
void DamageDonePowerUp::setDamageDone(int damageSet)
{
	damageGained = damageSet;
}
void DamageDonePowerUp::setTimeRemaining(int timeSet)
{
	timeLasting = timeSet;
}