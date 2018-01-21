#include <SFML/Graphics.hpp>
using namespace std;
#ifndef BabyHipHop_h
#define BabyHipHop_h
/*
	Baby hip hop extends SFML Sprite class
*/
class BabyHipHop : public sf::Sprite {
private:

public:
	BabyHipHop(int x, int y, sf::Texture &bulletTextureInput); //Constructor
};
#endif