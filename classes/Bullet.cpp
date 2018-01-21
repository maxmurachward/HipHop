#include "Bullet.h"
#include <iostream>

/*
	Constructor which takes two integers that represent position as its paramaters as well as a texture. Creates a bullet and sets it to 
	thaT position and texture. Also sets has hit to false and distance to fire remaining to 0. 
*/
Bullet::Bullet(int x, int y, sf::Texture &bulletTextureInput)
{
	distanceToFireRemaining = 0;
	setPosition(x, y);
	setTexture(bulletTextureInput);
	hitSprite = false;
}
/*
	Constructor which takes two integers that represent position as its paramaters as well as a texture and damge done. Creates a bullet and sets it to 
	tha position and texture. Also sets has hit to false and distance to fire remaining to 0. Damage done per bullet is also set
*/
Bullet::Bullet(int x, int y, sf::Texture &bulletTextureInput, int damageInput)
{
	distanceToFireRemaining = 0;
	setPosition(x, y);
	setTexture(bulletTextureInput);
	hitSprite = false;
	damageDone = damageInput;
	damageDoneOriginal = damageInput;
}
/*
	Constructor which takes two integers that represent position as its paramaters as well as a texture and damge done. Also takes speed to fire as its input also. Creates a bullet and sets it to 
	tha position and texture. Also sets has hit to false and distance to fire remaining to 0. Damage done per bullet is also set. Speed to fire also set
*/
Bullet::Bullet(int x, int y, sf::Texture &bulletTextureInput, int damageInput, float speedTofireInput)
{
	distanceToFireRemaining = 0;
	setPosition(x, y);
	bulletTexture = bulletTextureInput;
	setTexture(bulletTextureInput);
	hitSprite = false;
	damageDone = damageInput;
 	speedToFire = speedTofireInput;
	damageDoneOriginal = damageInput;
}
/*
	Blank constructor 
*/
Bullet::Bullet()
{

}
/*
	Returns how speed to fire at
*/
float Bullet::getSpeedToFire()
{
	return speedToFire;
}
/*
	Gets distance remaining
*/
int Bullet::getDistanceRemaining()
{
	return distanceToFireRemaining;
}
/*
	Set distance remaining
*/
void Bullet::setDistanceRemaining(int setter)
{
	distanceToFireRemaining = setter;
}
/*
	Returns has hit sprite boolean
*/
bool Bullet::getHitSprite()
{
	return hitSprite;
}
/*
	Set has hit sprite boolean
*/
void Bullet::setHitSprite(bool set)
{
	hitSprite = set;
}
/*
	Set amount of damage tobe done
*/
void Bullet::setDamageDone(int damageDoneInput)
{
	damageDone = damageDoneInput;
}
/*
	Returns amount of damage to be done per bullet
*/
int Bullet::getDamageDone()
{
	return damageDone;
}
/*
	Checks to see if the bullet has been flipped
*/
bool Bullet::isFlipped()
{
	return flipped;
}
/*
	Set the bullet to be flipped or not
*/
void Bullet::setFlipped(bool flippedInput)
{
	flipped = flippedInput;
}
/*
	Return the original damage done
*/
int Bullet::getOriginalDamageDone()
{
	return damageDoneOriginal;
}
