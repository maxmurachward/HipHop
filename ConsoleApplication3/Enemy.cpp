#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
/*
	Instance of an enemy is created, takes file name as an input, this will be its texture. Also takes speed as its input, this will be speed of movement. Takes X and Y positiion as its input.
	Also takes and health and damage done as this will represent the amount of damage it does to a player. Finally it takes a bullet texture to represent its bullets. A health bar is also
	created with the enemy. 
*/
Enemy::Enemy(string fileNameInput, float speedInput, int timeToMoveForInput, int xInput, int yInput, int healthInput, int damageDoneInput, sf::Texture &bulletTextureInput)
{
	fileName = fileNameInput;
	speed = speedInput;
	timeToMoveFor = timeToMoveForInput;
	x = xInput;
	y = yInput;
	setPosition(x,y);
	fireFinished = false;
	fireActivated = false;
	health = healthInput;
	startingHealth = healthInput;
	healthBar = new HealthBar();
	(*healthBar).setPosition((getPosition().x - 20) , (getPosition().y - 25)); // Need to obtain mid section of the enemy
	damageDone = damageDoneInput;
	enemyTexture.loadFromFile(fileName);
	setTexture(enemyTexture);
	bulletTexture = bulletTextureInput;
}
/*
	Empty instance of a enemy created
*/
Enemy::Enemy()
{

}
/*
	Returns starting health of the enemy
*/
int Enemy::getStartingHealth()
{
	return startingHealth;
}
/*
	Returns the enemy file name
*/
string Enemy::getFileName()
{
	return fileName;
}
/*
	Set the speed of the enemy to be the given input, number can be a float
*/
void Enemy::setSpeed(float speedInput)
{
	speed = speedInput;
}
/*
	Set the time for the enemy to move for, must be a int
*/
void Enemy::setTimeToMoveFor(int timeInput)
{
	timeToMoveFor = timeInput;
}
/*
	Set the file name of the enemy, must be a string
*/
void Enemy::setFileName(string fileNameInput)
{
	fileName = fileNameInput;
}
/*
	Returns the X position of the enemy
*/
int Enemy::getX()
{
	return x;
}
/*
	Returns the Y position of the enemy
*/
int Enemy::getY()
{
	return y;
}
/*
	Sets the Y position of the enemy
*/
void Enemy::setY(int yInput)
{
	y = yInput;
}
/*
	Sets the X position of the enemy
*/
void Enemy::setX(int xInput)
{
	x = xInput;
}
/*
	Returns the speed of the enemy 
*/
float Enemy::getSpeed()
{
	return speed;
}
/*
	Returns the time the enemy is moving for
*/
int Enemy::getTimeToMoveFor()
{
	return timeToMoveFor;
}
/*
	Sets the distance left to fire
*/
void Enemy::setDistanceToFire(int distanceToFireInput)
{
	distanceToFire = distanceToFireInput;
}
/*
	Returns the distance left to fire
*/
int Enemy::getDistanceToFire()
{
	return distanceToFire;
}
/*
	Returns a true or false whether or not firing is activated
*/
bool Enemy::getFireActivated()
{
	return fireActivated;
}
/*
	Sets the distance to fire remaining
*/
void Enemy::setDistanceToFireRemaining(int distanceToFireRemainingInput)
{
	distanceToFireRemaining = distanceToFireRemainingInput;
}
/*
	Returns the distance to fire remaining
*/
int Enemy::getDistanceToFireRemaining()
{
	return distanceToFireRemaining;
}
/*
	Returns the bullet of the enemy
*/
Bullet &Enemy::getBullet()
{
	return bullet;
}
/*
	Returns whether or not the enemy has stopped shooting
*/
bool Enemy::getFireFinished()
{
	return fireFinished;
}
/*
	Set fire finished to be true or false
*/
void Enemy::setFireFinished(bool fireFinishedInput)
{
	fireFinished = fireFinishedInput;
}
/*
	Return the amount of time between shooting
*/
int Enemy::getIntervalBetweenShooting()
{
	return intervalBetweenShooting;
}
/*
	Set the amount of time between shooting
*/
void Enemy::setintervalBetweenShooting(int intervalSet)
{
	intervalBetweenShooting = intervalSet;
}
/*
	Set speed to fire as a float taken as a parameter
*/
void Enemy::setSpeedToFire(float speed)
{
	speedToFire = speed;
}
/*
	Return the speed to fire
*/
float Enemy::getSpeedToFire()
{
	return speedToFire;
}
/*
	Gets the bullets X position
*/
int Enemy::getXBulletPosition()
{
	return xBulletPosition;
}
/*
	Set the bullets X position
*/
void Enemy::setXBulletPosition(int x)
{
	xBulletPosition = x;
}
/*
	Get the bullets Y position
*/
int Enemy::getYBulletPosition()
{
	return yBulletPosition;
}
/*
	Set the bullets Y position
*/
void Enemy::setYBulletPosition(int y)
{
	yBulletPosition = y;
}
/*
	Sets up the enemies shooting, sets the distance to fire for, the intervals to fire at and the speed to do so at
*/
void Enemy::shootingSetUp(int distance, int interval, float speed)
{
	setDistanceToFire(distance);
	setintervalBetweenShooting(interval);
	setSpeedToFire(speed);
}
/*
	Sets fire activated to be either true or false
*/
void Enemy::setFireActivated(bool boolean)
{
	fireActivated = boolean;
}
/*
	Set health of the enemy to be the input
*/
void Enemy::setHealth(int healthInput)
{
	health = healthInput;
}
/*
	Returns the health remaining of the enemy
*/
int Enemy::getHealth()
{
	return health;
}
/*
	Returns the amount of points given per kill
*/
int Enemy::getPointsGiven()
{
	return pointsGiven;
}
/*
	Sets the amount of points gained per kill
*/
void Enemy::setPointsGiven(int set)
{
	pointsGiven = set;
}
/*
	If fire is activated them move the bullet by the given speed
*/
void Enemy::fire(sf::Clock &clock, sf::RenderWindow &window)
{
	if (fireActivated == true)
	{
			bullet.move(sf::Vector2f(-getSpeedToFire(), 0));
	}
}
/*
	Set the fire to be activated and draw a bullet on the screen
*/
void Enemy::setFireActivated(bool fireAcitvatedInput, sf::RenderWindow &window)
{
	fireActivated = fireAcitvatedInput;
	fireFinished = false;
	bulletDead = false;
	sf::Vector2f position = getPosition();
	xBulletPosition = position.x;
	yBulletPosition = position.y;
	bullet.setDistanceRemaining(0);
	bullet = Bullet(xBulletPosition, yBulletPosition, bulletTexture, damageDone, speedToFire);
	window.draw(bullet);
}
/*
	Enable the enemy to move by itself. Returns whether the enemy has flipped itself or not
*/
bool Enemy::autoMove(sf::Clock &clock)
{
	bool switchOccured = false;
	sf::Time elapsed1 = clock.getElapsedTime(); // Amount of time elapsed
	int seconds = elapsed1.asSeconds();
	if (seconds == getTimeToMoveFor()) //If amount of time elapsed equals get time to move for then switch the enemys moving position. 
	{
		float speedEnemy = getSpeed();
		if (speedEnemy < 0) //If speed less then 0 then flip it to postive
		{
			speedEnemy = fabsf(speedEnemy);
			setSpeed(speedEnemy);
			switchOccured = true;
			clock.restart();

		}
		else //Else if speed greater then 0 then flip to be negative 
		{
			setSpeed(-speedEnemy);
			switchOccured = true;
			clock.restart();
		}
	}
	sf::Vector2f position = getPosition(); // Update position
	x = position.x;
	y = position.y;
	move(sf::Vector2f(getSpeed(), 0)); //Move by the given new speed
	(*healthBar).move(getSpeed(), 0);
	return switchOccured;
}
/*
	Returns the bullet of the enemy after death
*/
bool Enemy::getBulletDead()
{
	return bulletDead;
}
/*
	Sets the dead enemies bullet
*/
void Enemy::setBulletDead(bool input)
{
	bulletDead = input;
}
/*
	Delete this
*/
void Enemy::DisposeObject()
{
	delete this;
}
/*
	Returns enemys health bar
*/
HealthBar &Enemy::getHealthBar()
{
	return (*healthBar);
}
/*
	Sets the health bar of the enemy
*/
void Enemy::setHealthBar(HealthBar *input)
{
	healthBar = input;
}

