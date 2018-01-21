#include <SFML/Graphics.hpp>
using namespace std;
#ifndef HealthBar_h
#define HealthBar_h
class HealthBar : public sf::Sprite {
	private:
		sf::RectangleShape bottomLayer; //Red layer for the Health
		sf::RectangleShape healthLayer; //Green Layer for remaining health 
	public: 
		HealthBar();
		void drawHealthBar(sf::RenderWindow &window);
		sf::RectangleShape getHealthLayer();
		void setHealthLayer(sf::RectangleShape);
		sf::RectangleShape getBottomLayer();
		void setBottomLayer(sf::RectangleShape);
		void setPosition(int x, int y);
		void move(float x, float y);
		void setSizeHealthLayer(float x, float y);
};
#endif