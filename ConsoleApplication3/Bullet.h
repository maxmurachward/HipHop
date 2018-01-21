#include <SFML/Graphics.hpp>
using namespace std;
#ifndef Bullet_h
#define Bullet_h

class Bullet : public sf::Sprite {
private:
	int x;
	int y;
	int distanceToFireRemaining;
	sf::Texture bulletTexture; //Appearance of the bullet
	bool hitSprite; //Has the bullet hit someone
	int damageDone;
	bool flipped; //Is the bullet flipped
	float speedToFire; //Speed to fire the bullet at
	int damageDoneOriginal;
public:
	Bullet(int x, int y, sf::Texture &bulletTexture);
	Bullet(int x, int y, sf::Texture &bulletTexture, int damage);
	Bullet(int x, int y, sf::Texture &bulletTexture, int damage, float speedTofire);
	Bullet();
	void setDistanceRemaining(int setter);
	int getDistanceRemaining();
	bool getHitSprite();
	void setHitSprite(bool set);
	void setDamageDone(int damageDone);
	int getDamageDone();
	void setFlipped(bool);
	bool isFlipped();
	float getSpeedToFire();
	int getOriginalDamageDone();

};
#endif