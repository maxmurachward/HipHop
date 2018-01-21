#include <string>
#include <SFML/Graphics.hpp>

#ifndef PowerUp_h
#define PowerUp_h
using namespace std;

class PowerUp : public sf::Sprite {
private:
	sf::Texture powerUpTexture;
public:
	sf::Texture &getTexture();
};
#endif