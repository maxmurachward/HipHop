#include <string>
#include <SFML/Graphics.hpp>

#ifndef Enemy_h
#define Enemy_h
#include "Bullet.h"
#include "HealthBar.h"

using namespace std;


class Enemy : public sf::Sprite {
private:
	float speed;
	int timeToMoveFor;
	string fileName; //File name of the Enemy texture
	bool jumpEnabled; //Whether jump is enabled or not
	bool fireActivated; //Is fire activated or not
	int x;
	int y;
	int distanceToFire; //Amount to fire for
	Bullet bullet; //Bullet of the enemy 
	sf::Texture bulletTexture; //Bullet texture of the enemy
	int distanceToFireRemaining;
	bool fireFinished; //Has fire finished
	int intervalBetweenShooting; //Amount of time between shooting
	float speedToFire; //Speed to fire at
	int xBulletPosition;
	int yBulletPosition;
	int health; //Health of the Enemy
	int startingHealth; //Starting Health of the Enemy 
	HealthBar *healthBar; //Pointer to a health bar for the enemy 
	int damageDone; //Damage done by the enemy
	int pointsGiven; //Points given by the enemy
	sf::Texture enemyTexture; //Enemy texture
	string bulletName; //Name of the bullet texture
	bool bulletDead; //Is bullet off screen/hit enemy

public:

	Enemy(string fileNameInput, float speed, int timeToMoveForInput, int x, int y, int health, int damageDone, sf::Texture &bulletInput);
	Enemy();
	void setSpeed(float speed);
	void setTimeToMoveFor(int distance);
	void setFileName(string fileName);
	void setJumpEnabled(bool jumpEnabled);
	string getFileName();
	int getX();
	int getY();
	void setY(int y);
	void setX(int x);
	float getSpeed();	
	int getTimeToMoveFor();
	bool autoMove(sf::Clock &clock);
	void setDistanceToFire(int);
	int getDistanceToFire();
	void fire(sf::Clock &clock, sf::RenderWindow &window);
	void setFireActivated(bool, sf::RenderWindow &window);
	void setFireActivated(bool);
	bool getFireActivated();
	void setDistanceToFireRemaining(int remaining);
	int getDistanceToFireRemaining();
	Bullet &getBullet();
	bool getFireFinished();
	void setFireFinished(bool);
	int getIntervalBetweenShooting();
	void setintervalBetweenShooting(int);
	void setSpeedToFire(float);
	float getSpeedToFire();
	int getXBulletPosition();
	void setXBulletPosition(int x);
	int getYBulletPosition();
	void setYBulletPosition(int y);
	void shootingSetUp(int,int,float);
	void setHealth(int health);
	int getHealth();
	void Enemy::DisposeObject();
	HealthBar &getHealthBar();
	void setHealthBar(HealthBar *healthBar);
	int getStartingHealth();
	void setPointsGiven(int);
	int getPointsGiven();
	bool getBulletDead();
	void setBulletDead(bool);
};
#endif