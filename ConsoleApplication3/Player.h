#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "HealthBarPlayer.h"
#include <string>
using namespace std;

#ifndef Player_h
#define Player_h

class Player : public sf::Sprite {
public:
	Player();
	Player(int x, int y, int speed, int health);
	int getSpeed();
	void setSpeed(int);
	void draw(Player &player);
	sf::Texture texture;
	void fireActivate(sf::RenderWindow &window);
	void fireActivateFlipped(sf::RenderWindow &window);
	void setFireActivated (bool set);
	bool getFireActivated();
	Bullet &getBullet();
	HealthBarPlayer &getHealthBar();
	void setHealthBar(HealthBarPlayer *healthBar);
	void setHealth(int health);
	int getHealth();
	int getScore();
	void setScore(int);
	void moveBullet(bool isFlipped);
	bool getFlippedShooting();
	void drawBullets(sf::RenderWindow &window);
	vector<Bullet> &getBullets();
	void setOriginalSpeed(int);
	int getOriginalSpeed();
	void setDamageDone(int damageDone);
	int getDamageDone();
	int getOriginalDamageDone();
private:
	sf::Sprite sprite; //Player sprite
	int speed;
	string fileName; //File name of the texture for the Player
	bool fireActivated;
	Bullet bullet;
	sf::Texture bulletTextureNormal; //Normal bullet texture
	sf::Texture bulletTextureFlipped; //Flipped bullet texture
	int health;
	HealthBarPlayer *healthBar; //Pointer to an instance of a health bar
	int score;
	bool flippedShooting;
	std::vector<Bullet> bullets; //Vector to store all the bullets been fired
	int originalSpeed;
	int damageDoneOriginal;
	int damageDone;
};
#endif