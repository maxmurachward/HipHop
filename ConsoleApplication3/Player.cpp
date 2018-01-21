#include "Player.h"
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>

/*
	Blank constructor for the player
*/
Player::Player()
{

}
/*
	Creates an instance of a player, takes as parameters X Position, Y Position, Speed to move at and Health. It then sets the position to be this as well as set up its speed and health. 
	We also set the texture of the shooting and set the score to 0 here. 
*/
Player::Player(int xSet, int ySet, int speedSet, int healthInput)
{
	setPosition(xSet, ySet);
	speed = speedSet;
	fireActivated = false;
	health = healthInput;
	healthBar = new HealthBarPlayer();
	(*healthBar).setPosition((540), (-100)); // Need to obtain mid section of the player
	score = 0;
	bulletTextureNormal = sf::Texture();
	if (!bulletTextureNormal.loadFromFile("right_punch.png"))
	{
		// error...
	}
	bulletTextureFlipped = sf::Texture();
	if (!bulletTextureFlipped.loadFromFile("left_punch.png"))
	{
		// error...
	}
	damageDone = 10;
	damageDoneOriginal = 10;
}
/*
	Draws the texture for the player
*/
void Player::draw(Player &player)
{
	if (!texture.loadFromFile(fileName))
	{
			// error...
	}
	player.setTexture(texture);
}
/*
	Returns the speed the player moves at as a int
*/
int Player::getSpeed()
{
	return speed;
}
/*
	Sets the speed the player moves at
*/
void Player::setSpeed(int speedSet)
{
	speed = speedSet;
}
/*
	Creates a bullet based on the X and Y position of the player. It then adds it to its array of bullets and draws it on the screen. A render window to be drawn on is taken as
	a parameter
*/
void Player::fireActivate(sf::RenderWindow &window)
{
	flippedShooting = false;
	fireActivated = true;
	sf::Vector2f position = getPosition();
	int xBulletPosition = position.x + (getGlobalBounds().width / 2);
	int yBulletPosition = position.y - 20;
	if (fireActivated == false)
	{
		bullet = Bullet(xBulletPosition, yBulletPosition, bulletTextureNormal, damageDone);
		bullet.setFlipped(false);
		bullets.push_back(bullet);
		window.draw(bullet);
	}
	else if (fireActivated == true)
	{
		bullet = Bullet(xBulletPosition, yBulletPosition, bulletTextureNormal, damageDone);
		bullet.setFlipped(false);
		bullets.push_back(bullet);
		window.draw(bullet);
	}
}
/*
	Creates a flipped bullet based on the X and Y position of the player. It then adds it to its array of bullets and draws it on the screen. The bullet is flipped (Left Shooting). A render window to be drawn on is taken as
	a parameter
*/
void Player::fireActivateFlipped(sf::RenderWindow &window)
{
	flippedShooting = true;
	fireActivated = true;
	sf::Vector2f position = getPosition();
	int xBulletPosition = position.x - (getGlobalBounds().width / 2);
	int yBulletPosition = position.y - 20;
	if (fireActivated == false)
	{
		bullet = Bullet(xBulletPosition, yBulletPosition, bulletTextureFlipped, damageDone);
		bullet.setFlipped(true);
		bullets.push_back(bullet);
		window.draw(bullet);
	}
	else if (fireActivated == true)
	{
		bullet = Bullet(xBulletPosition, yBulletPosition, bulletTextureFlipped, damageDone);
		bullet.setFlipped(true);
		bullets.push_back(bullet);
		window.draw(bullet);
	}
}
/*
	For every bullet in the players array move the bullet, if flipped move left else right
*/
void Player::moveBullet(bool isFlipped)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i).isFlipped())
		{
			if (&bullets[i] != NULL)
			{
				bullets[i].move(sf::Vector2f(-12, 0));
			}
		}
		else if (bullets.at(i).isFlipped() == false)
		{
			if (&bullets[i] != NULL)
			{
				bullets[i].move(sf::Vector2f(12, 0));
			}
		}
	}
}
/*
	Draw all player bullets on screen
*/
void Player::drawBullets(sf::RenderWindow &window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (&bullets[i] != NULL)
		{
			window.draw(bullets[i]);
		}
	}
}
/*
	Returns the vector of bullets
*/
vector<Bullet> &Player::getBullets()
{
	return bullets;
}
/*
	Returns whether the player is currently firing a bullet or not
*/
bool Player::getFireActivated()
{
	return fireActivated;
}
/*
	Sets the fire activated to be either true or false
*/
void Player::setFireActivated(bool fireActivatedSet)
{
	fireActivated = fireActivatedSet;
}
/*
	Return a bullet
*/
Bullet &Player::getBullet()
{
	return bullet;
}
/*
	Returns the players health bar
*/
HealthBarPlayer &Player::getHealthBar()
{
	return (*healthBar);
}
/*
	Gives the player a health bar
*/
void Player::setHealthBar(HealthBarPlayer *healthBarInput)
{
	healthBar = healthBarInput;
}
/*
	Set the remaining health of the player
*/
void Player::setHealth(int healthInput)
{
	health = healthInput;
}
/*
	Returns the reamaining health of the player as a int
*/
int Player::getHealth()
{
	return health;
}
/*
	Returns the current score the player is on
*/
int Player::getScore()
{
	return score;
}
/*
	Sets the score the player is currently on as a int
*/
void Player::setScore(int set)
{
	score = set;
}
/*
	Returns whether or not the player is currently shooting flipped (Left)
*/
bool Player::getFlippedShooting()
{
	return flippedShooting;
}
/*
	Returns the original moving speed of the player
*/
int Player::getOriginalSpeed()
{
	return originalSpeed;
}
/*
	Sets the original speed of the player
*/
void Player::setOriginalSpeed(int speed)
{
	 originalSpeed = speed;
}
int Player::getOriginalDamageDone()
{
	return damageDoneOriginal;
}
void Player::setDamageDone(int damageDoneInput)
{
	damageDone = damageDoneInput;
}
/*
	Returns amount of damage to be done per bullet
*/
int Player::getDamageDone()
{
	return damageDone;
}