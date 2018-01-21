#include "UserInterface.h"
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>
/*
	Constructor for UI, creates the text for the score, time remaining and babys collected. Does all the text formatting and loading of the fonts also
*/
UserInterface::UserInterface()
{
	if (!font.loadFromFile("LONDO___.TTF"))
	{
		// error...
	}
	score.setFont(font); // font is a sf::Font
	time.setFont(font); // font is a sf::Font
	score.setCharacterSize(40); // in pixels, not points!
	score.setColor(sf::Color::Black);
	score.setStyle(sf::Text::Bold);
	time.setCharacterSize(40); // in pixels, not points!
	time.setColor(sf::Color::Black);
	time.setStyle(sf::Text::Bold);
	babyCollected.setFont(font);
	babyCollected.setCharacterSize(40); // in pixels, not points!
	babyCollected.setColor(sf::Color::Black);
	babyCollected.setStyle(sf::Text::Bold);
}
/*
	Set the string of the score part of the interface
*/
void UserInterface::setScore(string set)
{
	score.setString("Score: " + set);
}
/*
	Returns the string version of the score
*/
string UserInterface::getScore()
{
	string scoreString;
	scoreString = score.getString();
	return scoreString;
}
/*
	Sets the time remaining, set as a string not as a int
*/
void UserInterface::setTime(string set)
{
	time.setString(set);
}
/*
	Returns the time remaining as a string
*/
string UserInterface::getTime()
{
	string timeString;
	timeString = time.getString();
	return timeString;
}
/*
	Positions the time part of the user interface
*/
void UserInterface::setPositionTime(int x , int y)
{
	time.setPosition(x, y);
}
/*
	Sets the score part of the user interface
*/
void UserInterface::setPositionScore(int x, int y)
{
	score.setPosition(x, y);
}
/*
	Moves all parts of the user interface together
*/
void UserInterface::move(int x, int y)
{
	score.move(x, y);
	time.move(x, y);
	babyCollected.move(x, y);
}
/*
	Draws all parts of the user interface
*/
void UserInterface::draw(sf::RenderWindow &window)
{
	window.draw(score);
	window.draw(time);
	window.draw(babyCollected);
}
/*
	Positions the baby collected text on the screen
*/
void UserInterface::setPositionBabyCollected(int x, int y)
{
	babyCollected.setPosition(x, y);
}
/*
	Sets the amount of babys collected, pass a Int and conversion to string occurs
*/
void UserInterface::setBabyCollected(int collected)
{
	babyCollected.setString(std::to_string(collected));
}
