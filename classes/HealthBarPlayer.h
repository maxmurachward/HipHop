#include <SFML/Graphics.hpp>
using namespace std;
#ifndef HealthBarPlayer_h
#define HealthBarPlayer_h
class HealthBarPlayer : public sf::Sprite {
public:
	void draw(sf::RenderWindow &window);
	void setPosition(int x, int y);
	HealthBarPlayer();
	void move(int x, int y);
	void setLivesRemaining(int lives);
	int getLivesRemaining();
	int getPositionY();
	int getPositionX();
	int getHeight();
private: 
	sf::RectangleShape bottomLayer; //Rectangle for the bottom layer of the health bar
	sf::Sprite hearts[4]; //Hearts that represent health
	int gap; //Gap betweent the hearts
	sf::Texture heartsTexture; //Texture for the hearts
	int livesRemaining; 
};
#endif