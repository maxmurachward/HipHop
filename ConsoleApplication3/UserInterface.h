#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
#ifndef UserInterface_h
#define UserInterface_h

class UserInterface {
public:
	UserInterface();
	void setScore(string);
	string getScore();
	void setTime(string);
	string getTime();
	void setPositionTime(int, int);
	void setPositionScore(int, int);
	void move(int x, int y);
	void draw(sf::RenderWindow &window);
	void setPositionBabyCollected(int,int);
	void setBabyCollected(int);

private:
	sf::Font font; //Font of the User Interface
	sf::Text score; 
	sf::Text time;
	sf::Text babyCollected;
};
#endif