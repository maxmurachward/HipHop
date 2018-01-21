#include <SFML/Graphics.hpp>
using namespace std;
#ifndef HealthPowerUp_h
#define HealthPowerUp_h

class HealthPowerUp : public sf::Sprite {
private:
	sf::Texture heartsTexture; //Texture of the health power up
	int healthGained; 
public:
	HealthPowerUp();
	int getHealthGained();
};
#endif