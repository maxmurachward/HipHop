#include "HealthBar.h"
#include <iostream>

/*
	Creates an instance of the enemy health bar, sets two rectangles to be of equal size, one green and one red
*/
HealthBar::HealthBar()
{
	bottomLayer = sf::RectangleShape(sf::Vector2f(100, 5));
	bottomLayer.setFillColor(sf::Color(226, 10, 10));
	healthLayer = sf::RectangleShape(sf::Vector2f(100, 5));
	healthLayer.setFillColor(sf::Color(10, 226, 125));
}
/*
	The health bar is drawn on the screen
*/
void HealthBar::drawHealthBar(sf::RenderWindow &window)
{
	window.draw(bottomLayer);
	window.draw(healthLayer);
}
/*
	The health rectangle layer is returned
*/
sf::RectangleShape HealthBar::getHealthLayer()
{
	return healthLayer;
}
/*
	The health layer is set to be a given rectangle that has been input
*/
void HealthBar::setHealthLayer(sf::RectangleShape input)
{
	healthLayer = input;
}
/*
	Bottom layer is returned
*/
sf::RectangleShape HealthBar::getBottomLayer()
{
	return bottomLayer;
}
/*
	The bottom layer is set to be a given rectangle that has been input
*/
void HealthBar::setBottomLayer(sf::RectangleShape input)
{
	bottomLayer = input;
}
/*
	Position on screen of health bar set to the X and Y input
*/
void HealthBar::setPosition(int x, int y)
{
	bottomLayer.setPosition(x, y);
	healthLayer.setPosition(x, y);
}
/*
	Health bar moved by the given amount X and Y
*/
void HealthBar::move(float x, float y)
{
	bottomLayer.move(sf::Vector2f(x, y));
	healthLayer.move(sf::Vector2f(x, y));
}
/*
	Health layers is reduced/expanded by X and Y amount
*/
void HealthBar::setSizeHealthLayer(float x, float y)
{
	healthLayer.setSize(sf::Vector2f(x, y));
}

