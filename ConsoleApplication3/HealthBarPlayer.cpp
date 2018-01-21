#include "HealthBarPlayer.h"
#include <iostream>
/*
	Create a instance of a health bar for the player, creates a rectangle and 4 hearts to represent heatlh. Lives remaining is also set to the default value of 4
*/
HealthBarPlayer::HealthBarPlayer()
{
	bottomLayer = sf::RectangleShape(sf::Vector2f(80, 15));
	bottomLayer.setFillColor(sf::Color(0, 245, 255));
	gap = 3;
	heartsTexture.loadFromFile("heart.png");
	livesRemaining = 4;
	for (int i = 0; i < livesRemaining; i++)
	{
		hearts[i] = sf::Sprite();
		hearts[i].setTexture(heartsTexture);
	}
}
/*
	Sets the position of the health bar to be X and Y. The hearts are kept in the same place on the rectangle and moved equally
*/
void HealthBarPlayer::setPosition(int x, int y)
{
	gap = 3;
	bottomLayer.setPosition(x, y);
	for (int i = 0; i < livesRemaining; i++)
	{
		hearts[i].setPosition(x + gap, bottomLayer.getPosition().y + 2);
		gap = gap + 20;
	}
}
/*
	The health bar is drawn on screen
*/
void HealthBarPlayer::draw(sf::RenderWindow &window)
{
	window.draw(bottomLayer);
	for (int i = 0; i < livesRemaining; i++)
	{
		window.draw(hearts[i]);
	}
}
/*
	The health bar is moved by X amount of the X axis and Y amount on the Y axis
*/
void HealthBarPlayer::move(int x, int y)
{
	bottomLayer.move(sf::Vector2f(x, y));
	for (int i = 0; i < livesRemaining; i++)
	{
		hearts[i].move(sf::Vector2f(x, y));
	}
}
/*
	Lives remaining becomes the int lives. Must be greater than or equal to 0 and less than or equal to 4
*/
void HealthBarPlayer::setLivesRemaining(int lives)
{
	if (lives <= 4 && lives >= 0)
	{
		livesRemaining = lives;
	}
}
/*
	Returns the amount of lives the player has left
*/
int HealthBarPlayer::getLivesRemaining()
{
	return livesRemaining;
}
/*
	returns the Y position of the bottom layer of the health bar
*/
int HealthBarPlayer::getPositionY()
{
	return bottomLayer.getPosition().y;
}
/*
	Returns the X position of the bottom layer of the health bar
*/
int HealthBarPlayer::getPositionX()
{
	return bottomLayer.getPosition().x;
}
/*
	Return the height of the health bar
*/
int HealthBarPlayer::getHeight()
{
	return bottomLayer.getGlobalBounds().height;
}


