#include "BabyHipHop.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;

/*
	Constructor for the baby hip, extension of the sprite class from SFML. Creates a baby with a set texture and sets it to the position 
	defined within its constructor
*/
BabyHipHop::BabyHipHop(int x, int y, sf::Texture &bulletTextureInput)
{
	setTexture(bulletTextureInput);
	setPosition(x, y);
}