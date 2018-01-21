#include <SFML/Graphics.hpp>
using namespace std;
#ifndef SpeedPowerUp_h
#define SpeedPowerUp_h

class SpeedPowerUp : public sf::Sprite {
private:
	sf::Texture speedTexture; //Texture of the speed power up
	int speedGained; //Amount of speed gained from the pwoer up
	int timeLasting; //Time the power up lasts
public:
	SpeedPowerUp(int speed, int time);
	int getSpeed();
	int getTimeRemaining();
	void setSpeed(int);
	void setTimeRemaining(int);
};
#endif