#include <SFML/Graphics.hpp>
using namespace std;
#ifndef DamageDonePowerUp_h
#define DamageDonePowerUp_h

class DamageDonePowerUp : public sf::Sprite {
private:
	sf::Texture powerUpTexture; //Texture of the Damage power up
	int damageGained; //Amount of speed gained from the pwoer up
	int timeLasting; //Time the power up lasts
public:
	DamageDonePowerUp(int damageGained, int time);
	int getDamageGained();
	int getTimeRemaining();
	void setDamageDone(int);
	void setTimeRemaining(int);
};
#endif