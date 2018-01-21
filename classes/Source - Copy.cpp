//Count down timer for levels? Can be done quite easy, still want done?

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <SFML/Audio.hpp>
#include "Enemy.h"
#include "Player.h"
#include "HealthPowerUp.h"
#include "SpeedPowerUp.h"
#include "UserInterface.h"
#include "BabyHipHop.h"
#include "DamageDonePowerUp.h"
#include <vector>
#include <string>
#include <array>
bool godMode = true;
bool gameFinished = false;
using namespace std;
sf::Texture hip_array[21];
sf::Texture instructions_array[10];
sf::Texture pause_texture;
sf::Texture texture_2;
sf::Texture level2;
sf::Texture level3;
sf::Texture level4;
sf::Texture level5;
sf::Texture level10;
sf::Texture intro_texture;
sf::Texture hip_stationary;
sf::Texture game_over;
sf::Texture bossTexture;
sf::Texture game_finish;
sf::Texture quit_game;
sf::Music music;
int walk = 0; //Controls Hip images
sf::Sprite Pause_sprite; //Pause Screen
sf::Sprite intro_sprite;
sf::Sprite Background;
sf::Sprite gameOver_sprite;
sf::Sprite gameFinish_sprite;
sf::Sprite quit_sprite;
sf::Sprite instruction_sprite;
bool esc_press = false; //Checks if escape has been pressed
float position = 0; //Controls camera position 
bool setUp = false; //Checks to see if level loaded
bool flipped = false; //Checks position of Hip
int stepsSpeed = 0;
int screenYSize = 720;
int screenXSize = 1280;
bool enemyDead = false; //Checks if enemy dead
int enemyNumbers = 4; //Number of enemys on the screen
int healthPowerUps = 1; //number of Health power ups on the screen
int totalSpeedPowerUps = 2; //number of speed power ups on the screen
int totalDamageIncreasePowerUps = 2; //number of speed power ups on the screen
Enemy *enemy; //Pointer to enemys
Player *Hip; //Pointer to player
HealthPowerUp *healthPowerUp; //Pointer to health power up
HealthPowerUp *healthPowerUpArray[15]; //holds all the health power ups
SpeedPowerUp *speedPowerUp;
SpeedPowerUp *speedPowerUpArray[15]; //holds all the speed power ups
DamageDonePowerUp *damageIncreasePowerUp;
DamageDonePowerUp *damageIncreasePowerUpArray[15]; //holds all the damage increase power ups
UserInterface *userInterface; //Pointer to the user interface
sf::Clock gameClock; //clock to keep track of time
sf::RenderWindow window(sf::VideoMode(screenXSize, screenYSize), "Hip Hop Goes Hoppin"); //Game window
sf::View view; //game view
Enemy *enemyArray[50]; //array to hold enemies
sf::Clock clocks[50]; //array to hold clocks
bool enableFire = false; //Can the player fire
std::vector<int> secondsBeen; //Total amount of time been
float jumpSpeed = 10.0f; //Speed of jump
const float gravity = 1; //Speed of gravity
int groundHeight = 500; //Level ground at
sf::Vector2f velocity(sf::Vector2f(0, 0)); //Speed of movement
float maxHeight = -50; //Max height to jump
bool jumpEnabled = true; //Can you jump
bool hitEnemyOnTop = false; //Did you hit an enemy on top
sf::Texture enemyTexture; //enemy texture
int speedPowerUpTimeRemainig = -1; //Time left for powerups
int damageIncreaseTimeRemaining = -1;
std::vector<Bullet> deadEnemyBullets; //bullets of dead enemys if still on screen
sf::Texture tileTexture; //Texture of tile on screen
sf::Sprite tiles;
sf::Texture babyHipTexture; //Baby Hip texture
BabyHipHop *babyHipHop; //Pointer to baby hip
bool onGround = true; //Are you on the ground
bool onBox = false; //are you in the air on a box
const int height = 12; //Amount of tiles down
const int width = 80; //Amount of tile accross
bool onTile[height][width]; //What tile are you on
sf::RectangleShape *rectangleArray[height][width]; //Holds floor items
sf::Sprite *tilesArray[height][width]; //Holds tiles
sf::SoundBuffer punchSoundBuffer;
sf::Sound punchSound;
sf::SoundBuffer hitSoundBuffer;
sf::Sound hitSound;
sf::SoundBuffer jumpSoundBuffer;
sf::Sound jumpSound;

int knockbackAmount = 0;

int babyCollected = 0; //Amount of babies rescued
bool levelComplete = false; //Is the level complete
int level = 1; //Starting Level
int maxLevel = 6; //Maximum level number
int levelArray[height][width];   //Holds the tile map to the level
int score; //User Score

float timeRemaining = 60.0f; //Amount of time to play the level
sf::Clock timerClock; //clock to keep track of time
bool loadImages = false;

void instructions()
{
	int instrction_counter = 0;
	instruction_sprite.setTexture(instructions_array[0]);
	window.draw(instruction_sprite);
	window.display();
	bool done1 = false;
	bool done2 = false;
	bool done3 = false;
	while (1)
	{
		sf::sleep(sf::milliseconds(10));
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && instrction_counter < 5 && instrction_counter >= 0)
		{
			if (done1 == false)
			{
				instrction_counter++;
				cout << instrction_counter << "\n";
				instruction_sprite.setTexture(instructions_array[instrction_counter]);
				window.draw(instruction_sprite);
				window.display();
				done1 = true;
			}
		}
		done1 = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && instrction_counter <= 5 && instrction_counter >0)
		{

			if (done2 == false)
			{
				instrction_counter--;
				cout << instrction_counter << "\n";
				instruction_sprite.setTexture(instructions_array[instrction_counter]);
				window.draw(instruction_sprite);
				window.display();
				done2 = true;
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && instrction_counter <= 5 && instrction_counter >0)
		{
			done2 = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			done3 = true;
		}
		if (done3 == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return;
		}
	}
}
void quit()
{
	bool done = false;
	while (1)
	{
		window.draw(quit_sprite);
		window.display();
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		{
			sf::sleep(sf::milliseconds(30));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
				exit(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
			{
				done = true;
			}
			if (done == true && !(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)))
			{
				return;
			}
		}
	}
}
//Applys knockback to the player
void applyKnockback(int amount)
{
	(*Hip).move(-amount, 0);
	(*Hip).getHealthBar().setPosition((*Hip).getPosition().x, (*Hip).getPosition().y - 80);
	if (knockbackAmount>0)	//Reduce knockback amount by 25 each frame until 0
	{
		knockbackAmount -= 25;
	}
	if (knockbackAmount<0)	//Safeguard just in case knockback amount drops below 0
	{
		knockbackAmount = 0;
	}


}
//Moves the character on the screen, moves his health bar and the user interface alongside it
void userCharacterMove(int x, int y)
{
	(*Hip).move(x, y);
	(*Hip).getHealthBar().move(x, y);
	(*userInterface).move(x, y);
}
//Checks if the sprite has fallen off a tile and is below the floor
void belowFloorDetection(Player &sprite)
{
	if (sprite.getPosition().y > 350)
	{
		sprite.setHealth(0);
	}
}
//Remove all the tiles and floor items from the holders
void emptyRectangleArrayAndTilesArray()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			rectangleArray[i][j] = NULL;
			tilesArray[i][j] = NULL;
		}
	}
}
//Checks if the user has hit a baby and ends the level and moves to the next level if true. This is the END point of the level
void hitBaby(BabyHipHop &baby)
{
	sf::FloatRect hipBox = (*Hip).getGlobalBounds();
	sf::FloatRect babyBox = baby.getGlobalBounds();
	if (hipBox.intersects(babyBox))
	{
		if (level == maxLevel)
		{
			//GAME OVER SCREEN HERE/You WIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!     
			//*************************************************************************************************************************************
			cout << "Game Over" << "\n";
			//Reset all Global Variables to initial state
			gameFinished = true;
		}
		else
		{
			score = (*Hip).getScore();
			secondsBeen.clear();
			cout << "Level Complete";
			babyCollected++;
			(*userInterface).setBabyCollected(babyCollected);
			levelComplete = true;
			setUp = false;
			level++;
			gameClock.restart();
			walk = 0; //Controls Hip images
			esc_press = false; //Checks if escape has been pressed
			position = 0; //Controls camera position 
			setUp = false; //Checks to see if level loaded
			flipped = false; //Checks position of Hip
			stepsSpeed = 0;
			enemyDead = false; //Checks if enemy dead
			enableFire = false; //Can the player fire
			jumpSpeed = 10.0f; //Speed of jump
			groundHeight = 500; //Level ground at
			maxHeight = -50; //Max height to jump
			jumpEnabled = true; //Can you jump
			hitEnemyOnTop = false; //Did you hit an enemy on top
			speedPowerUpTimeRemainig = -1; //Time left for powerups
			onGround = true; //Are you on the ground
			onBox = true; //are you in the air on a box
			levelComplete = false; //Is the level complete
			Hip = NULL;
		}
	}
}

//Sets up the level by placing the tiles and floor in the right place
void levelSetUp(int(&level)[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			levelArray[i][j] = level[i][j];
			if (levelArray[i][j] == 2)
			{
				sf::RectangleShape *rectangle = new sf::RectangleShape(sf::Vector2f(64, 64));
				rectangleArray[i][j] = rectangle;
			}
			if (levelArray[i][j] == 1)
			{
				sf::Sprite *tiles = new sf::Sprite;
				tilesArray[i][j] = tiles;
			}
		}
	}
}
//Checks if the player has hit a tile or floor and detects whether he needs to fall down 
void levelCollisionDetection()
{
	sf::FloatRect hipBox = (*Hip).getGlobalBounds(); //Gets hip bounds
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (levelArray[i][j] == 2) //If we are on a floor piece
			{
				(*rectangleArray[i][j]).setFillColor(sf::Color::Transparent); //Make it clear
				(*rectangleArray[i][j]).setPosition(j * 64, i * 64 - 540); //Set the position of it on the screen, box is 64 big
				window.draw(*rectangleArray[i][j]);
				sf::FloatRect otherBox = (*rectangleArray[i][j]).getGlobalBounds(); //Get bounds of the box
				if (hipBox.intersects(otherBox)) //If it hits hip then set hip to fall off the screen
				{
					groundHeight = 500;
				}
			}
			if (levelArray[i][j] == 1) //If  we are on a normal tile
			{
				(*tilesArray[i][j]).setPosition(j * 64, i * 64 - 540); //Set position of tile
				(*tilesArray[i][j]).setTexture(tileTexture); //Set texture
				window.draw((*tilesArray[i][j]));
				sf::FloatRect otherBox = (*tilesArray[i][j]).getGlobalBounds(); //Get bounds of the tile
				sf::Vector2f difference = sf::Vector2f((*Hip).getPosition().x - (*tilesArray[i][j]).getPosition().x, (*tilesArray[i][j]).getPosition().y - (*Hip).getPosition().y); //Work out the difference of the intersection
				if (hipBox.intersects(otherBox)) //If hip hits a tile work out if it was on the ground or in the air and which angle it hit the tile at
				{
					if (onGround) //If hip is on the floor
					{
						if (difference.y > difference.x && difference.y > -difference.x && i < height - 1)	//Collision with Top of tile (ceiling), must of jumped onto a tile
						{
							groundHeight = (*tilesArray[i][j]).getPosition().y + (*tilesArray[i][j]).getGlobalBounds().height + 1; //Ground becomes top of this tile
							maxHeight = (*tilesArray[i][j]).getPosition().y - 250; //Max height to jump is 200 above this point
							onBox = true;
							onGround = false;
						}
						else if (difference.y > difference.x && difference.y < -difference.x && i < height - 1)	//Collision with left side of tile (wall)
						{
							userCharacterMove(-10, 0);
						}
						else if (difference.y < difference.x && difference.y > -difference.x && i < height - 1)	//Collision with right side of tile (wall)
						{
							userCharacterMove(10, 0);
						}
						else if (difference.y < difference.x && difference.y < -difference.x && i < height - 1)	//Collision with Bottom of tile (floor)
						{
							(*Hip).move(0, 10);
							(*Hip).getHealthBar().move(0, 10);
						}
						else if (difference.y > difference.x && difference.y > -difference.x && i == height - 1) //Checks if we hit another tile on the ground level (==)
						{
							groundHeight = (*tilesArray[i][j]).getPosition().y + (*tilesArray[i][j]).getGlobalBounds().height + 1;
							maxHeight = (*tilesArray[i][j]).getPosition().y - 200;
							onGround = true;
							onBox = false;
						}
					}
					if (onBox) //If hip is not on the ground but instead on a box in the air
					{
						if (difference.y > difference.x && difference.y > -difference.x)	//Collision with Top of tile (ceiling)
						{
							groundHeight = (*tilesArray[i][j]).getPosition().y + (*tilesArray[i][j]).getGlobalBounds().height + 1; //Ground height becomes top of box Y
							maxHeight = (*tilesArray[i][j]).getPosition().y - 250;
							onTile[i][j] = true; //Confirms the we are on this tile
						}
						else if ((difference.y > difference.x && difference.y < -difference.x && (onTile[i][j] == false && onTile[i][j + 1] == false)) && (difference.y > difference.x && difference.y < -difference.x && (onTile[i][j] == false && onTile[i][j - 1] == false)))	//Collision with right side of tile and that tile to the right or left of you (wall)
						{
							(*Hip).move(sf::Vector2f(-10, 0));
						}
						else if (difference.y > difference.x && difference.y < -difference.x && i < height - 1)	//Collision with left side of tile (wall)
						{
							userCharacterMove(-10, 0);
						}
						else //We havent hit a tile so we must fall down
						{
							onGround = true; //Fall to floor
							onBox = false;
							groundHeight = 500;
							onTile[i][j] = false; //No longer on this tile
						}
					}
				}
				else if (onTile[i][j] == true) //If still on tile but not collided with anything then must fall down and reset values to floor values
				{
					onGround = true;
					onBox = false;
					groundHeight = 500;
					onTile[i][j] = false;
				}
			}
		}
	}
}
//Move the AI
void AIMove(Enemy &enemy, sf::Clock &enemyClock)
{
	if (enemy.getHealth() > 0)
	{
		enemy.autoMove(enemyClock);
		window.draw(enemy);
	}
}
//Set fire activated for AI if after certain time, draw bullet and fire it every time
void AIFire(Enemy &enemy, sf::Clock &enemyClock, Player &sprite)
{
	//Acitvate bullet if after certains seconds
	if (((int)gameClock.getElapsedTime().asSeconds() % enemy.getIntervalBetweenShooting()) == 0 && (int)gameClock.getElapsedTime().asSeconds() != 0 && enemy.getHealth() > 0)
	{
		if (enemy.getFireActivated() == false)
		{
			enemy.setFireActivated(true, window);
		}
	}
	//If bullet off the screen then remove it
	if ((enemy.getBullet().getPosition().x < (sprite.getPosition().x - (screenXSize / 2)) && enemy.getBulletDead() == false))
	{
		cout << "OFF SCREEN ENEMY BULLET" << "\n";
		enemy.setFireActivated(false);
		enemy.setFireFinished(true);
		enemy.getBullet().setPosition(-1000, -1000);
		enemy.setBulletDead(true);
	}
	//If the bullet is still on the screen then draw it and move it
	if (enemy.getFireFinished() == false && enemy.getBullet().getHitSprite() == false)
	{
		enemy.fire(gameClock, window);
		window.draw(enemy.getBullet());
	}
}
//Move dead enemies bullets
void deadEnemyBulletsFire(Player &sprite)
{
	for (int i = 0; i < deadEnemyBullets.size(); i++)
	{
		//Remove if off screen
		if ((deadEnemyBullets[i].getPosition().x < (sprite.getPosition().x - (screenXSize / 2))))
		{
			cout << "OFF SCREEN DEAD ENEMY BULLET" << "\n";
			deadEnemyBullets.erase(deadEnemyBullets.begin() + i);
		}
		//move and draw the bullet
		else
		{
			deadEnemyBullets[i].move(-deadEnemyBullets[i].getSpeedToFire(), 0);
			deadEnemyBullets[i].setTexture(enemyTexture);
			window.draw(deadEnemyBullets[i]);
		}
	}
}
//Detects whether the player has hit the enemy, reduces health if did
void DetectHitSprite(Player &sprite, Enemy &enemy)
{
	sf::FloatRect spriteBoundingBox = sprite.getGlobalBounds();
	sf::FloatRect enemyBoundingBox = enemy.getBullet().getGlobalBounds();
	if (spriteBoundingBox.intersects(enemyBoundingBox))
	{
		cout << "Hit" << "\n";
		sprite.setHealth(sprite.getHealth() - enemy.getBullet().getDamageDone());
		cout << sprite.getHealth() << "\n";
		sprite.getHealthBar().setLivesRemaining(sprite.getHealthBar().getLivesRemaining() - 1);
		enemy.getBullet().setHitSprite(true);
		enemy.getBullet().setPosition(0, 0);
	}
}
//Detects whether dead enemy bullet hits player, reduces health if did
void deadEnemyBulletHitDetect(Player &sprite)
{
	for (int i = 0; i < deadEnemyBullets.size(); i++)
	{
		sf::FloatRect spriteBoundingBox = sprite.getGlobalBounds();
		sf::FloatRect enemyBoundingBox = deadEnemyBullets[i].getGlobalBounds();
		if (spriteBoundingBox.intersects(enemyBoundingBox))
		{
			sprite.setHealth(sprite.getHealth() - deadEnemyBullets[i].getDamageDone());
			cout << sprite.getHealth() << "\n";
			sprite.getHealthBar().setLivesRemaining(sprite.getHealthBar().getLivesRemaining() - 1);
			deadEnemyBullets[i].setHitSprite(true);
			cout << "Dead Enemy Bullet Hit" << "\n";
			deadEnemyBullets.erase(deadEnemyBullets.begin() + i);
		}
	}
}
//If player hits the sprite then knock him back and remove lives
void playerHitSpriteDetection(Player &sprite, Enemy &enemy)
{
	hitEnemyOnTop = false; //Check to see where hit enemy
	int pushBackDistance = 100;
	sf::FloatRect spriteBoundingBox = sprite.getGlobalBounds();
	sf::FloatRect enemyBoundingBox = enemy.getGlobalBounds();
	if (spriteBoundingBox.intersects(enemyBoundingBox))
	{
		if (sprite.getPosition().y < enemy.getPosition().y) //If hit on top then dont push back
		{
			hitEnemyOnTop = true;
		}
		else //If not hit on top then redcue score and health and reset to start position
		{
			hitEnemyOnTop = false;
			sprite.setScore(sprite.getScore() - enemy.getPointsGiven());
			cout << sprite.getScore() << " points lost" << "\n";
			cout << "Hit enemy Sprite" << "\n";
			sprite.setHealth(sprite.getHealth() - 25);
			cout << sprite.getHealth() << "\n";
			sprite.getHealthBar().setLivesRemaining(sprite.getHealthBar().getLivesRemaining() - 1);
			//				position = position - pushBackDistance;
			//				sprite.setPosition(574, 0);
			//				sprite.getHealthBar().setPosition(540, (*Hip).getPosition().y - 100);
			sprite.move(-75, 0);
			sprite.getHealthBar().setPosition((*Hip).getPosition().x, (*Hip).getPosition().y - 80);
			knockbackAmount = 75;
			enemy.getBullet().setPosition(-10000, -10000);
			(*userInterface).setPositionScore(0, -500);
			(*userInterface).setPositionTime(screenXSize - 75, -500);
			window.setView(view);
		}
	}
}
//Draw player
void PlayerDraw(Player &player)
{
	window.draw(player);
}
//Checks whether the player bullet has hit the enemy. Reduces the enemy health appropriately 
void playerFireCollision(Player &sprite, Enemy &enemy)
{
	for (int i = 0; i < sprite.getBullets().size(); i++) //Goes round all the bullets fired 
	{
		sf::FloatRect spriteBoundingBox = sprite.getBullets().at(i).getGlobalBounds();
		sf::FloatRect enemyBoundingBox = enemy.getGlobalBounds();
		if (spriteBoundingBox.intersects(enemyBoundingBox)) //If hit enemy
		{
			cout << "Enemy Hit" << "\n";
			hitSound.play();
			enemy.setHealth(enemy.getHealth() - sprite.getBullet().getDamageDone()); //Reduce health of enemy
			double hitsPossible = (double)enemy.getStartingHealth() / (double)sprite.getBullet().getDamageDone(); //Work out hits allowed before death
			int reduceHealthBarPerTime = enemy.getHealthBar().getBottomLayer().getGlobalBounds().width / hitsPossible; //Amount of damaged caused
			enemy.getHealthBar().setSizeHealthLayer((enemy.getHealthBar().getHealthLayer().getSize().x - reduceHealthBarPerTime), 5); //Lower health 
			sprite.getBullets().erase(sprite.getBullets().begin() + i); //remove bullet
			if (sprite.getBullets().size() == 0) //if no bullets left then fire activated no longer true
			{
				sprite.setFireActivated(false);
			}
		}
	}
}
//Checks to see if players bullets off screen, if they are then they are removed
void bulletOffScreenDetection(Player &sprite)
{
	for (int i = 0; i < sprite.getBullets().size(); i++) //For every bullet
	{

		if (sprite.getBullets().at(i).getPosition().x >(sprite.getPosition().x + (screenXSize / 2))) //If greater than right hand side of screen erase it
		{
			sprite.getBullets().erase(sprite.getBullets().begin() + i);
			if (sprite.getBullets().size() == 0)
			{
				sprite.setFireActivated(false);
			}
			cout << "Off Screen" << "\n";
		}
		else if (sprite.getBullets().at(i).getPosition().x <  (sprite.getPosition().x - (screenXSize / 2))) //If greater than left hand side of screen erase it
		{
			sprite.getBullets().erase(sprite.getBullets().begin() + i);
			if (sprite.getBullets().size() == 0)
			{
				sprite.setFireActivated(false);
			}
			cout << "Off Screen" << "\n";
		}
	}
}
//Has the player hit the power up, return true if yes or false if hasnt, increase health by power up amount
bool intersectHealthPowerUp(Player &sprite, HealthPowerUp &powerUp)
{
	sf::FloatRect spriteBoundingBox = sprite.getGlobalBounds();
	sf::FloatRect powerUpBoundingBox = powerUp.getGlobalBounds();
	if (spriteBoundingBox.intersects(powerUpBoundingBox))
	{
		if ((*Hip).getHealth() < 100)
		{
			cout << "Hit" << "\n";
			sprite.setHealth(sprite.getHealth() + powerUp.getHealthGained());
			cout << sprite.getHealth() << "\n";
			sprite.getHealthBar().setLivesRemaining(sprite.getHealthBar().getLivesRemaining() + 1);
			return true;
		}
	}
	return false;
}
//Has the player hit the power up, return true if yes or false if hasnt, increase speed by power up amount
bool intersectSpeedPowerUp(Player &sprite, SpeedPowerUp &powerUp)
{
	sf::FloatRect spriteBoundingBox = sprite.getGlobalBounds();
	sf::FloatRect powerUpBoundingBox = powerUp.getGlobalBounds();
	if (spriteBoundingBox.intersects(powerUpBoundingBox))
	{
		cout << "Hit" << "\n";
		sprite.setOriginalSpeed(sprite.getSpeed());
		speedPowerUpTimeRemainig = powerUp.getTimeRemaining();
		sprite.setSpeed(powerUp.getSpeed());
		return true;
	}
	return false;
}
//Has the player hit the power up, return true if yes or false if hasnt, increase damage by power up amount
bool intersectDamageIncreasePowerUp(Player &sprite, DamageDonePowerUp &powerUp)
{
	sf::FloatRect spriteBoundingBox = sprite.getGlobalBounds();
	sf::FloatRect powerUpBoundingBox = powerUp.getGlobalBounds();
	if (spriteBoundingBox.intersects(powerUpBoundingBox))
	{
		sprite.setDamageDone(powerUp.getDamageGained());
		damageIncreaseTimeRemaining = powerUp.getTimeRemaining();
		return true;
	}
	return false;
}
//Hip hop animations 
void anim()
{
	(*Hip).setTexture(hip_array[walk]);
	if (stepsSpeed == 1)
	{
		walk++;
		stepsSpeed = 0;
	}
	else
	{
		stepsSpeed++;
	}

	if (walk == 21)
	{
		walk = 0;
	}
}
//Occurs when the pause screen is accessed
void pause()
{
	window.draw(Pause_sprite);
	window.display();
	while (1)
	{
		sf::sleep(sf::milliseconds(10));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		{
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		{
			quit();
			break;
		}
	}
}
//Introduction screen
void intro()
{
	if (!music.openFromFile("Intro.ogg"))
		printf("ERROR cant load music");// error
	music.play();
	music.setLoop(1);


	while (1)
	{
		window.draw(intro_sprite);
		window.display();
		sf::sleep(sf::milliseconds(10));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		{
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		{
			instructions();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			exit(0);
		}
	}
}


//Checks to see whether a second has been before
bool hasSecondBeen(int second)
{
	for (int i = 0; i < secondsBeen.size(); i++)
	{
		if (second == secondsBeen[i])
		{
			return true;
		}
	}
	return false;
}
//Movement for Hip Hop, includes jump and gravity
void movement()
{
	applyKnockback(knockbackAmount);	//Makes knockback work
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Space bar starts jump
	{
		if (velocity.y > maxHeight && jumpEnabled) // If jump is allowed and we are not at max height then start the jump
		{
			jumpSound.play();
			velocity.y = -jumpSpeed;
		}
		if ((*Hip).getPosition().y < maxHeight) //If we hit max height then stop jumping
		{
			jumpEnabled = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //If D pressed flip Hip Hop  the right way and move the camera and hip hop
	{
		if (Hip != NULL && knockbackAmount == 0)
		{
			anim();
			if (flipped == true)
			{
				(*Hip).scale(-1.f, 1.f);
				flipped = false;
			}
			else
			{
				position = position + (*Hip).getSpeed();
				velocity.x = (*Hip).getSpeed();
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //If f pressed and Hip exists then set fire to be acitvated depending on which way he is facing
	{
		if (Hip != NULL)
		{
			if (flipped == false && enableFire == true) //Not flipped then fire normally
			{
				(*Hip).fireActivate(window);
				enableFire = false;
				punchSound.play();
			}
			else if (flipped == true && enableFire == true) //If flipped then fire backwards
			{
				(*Hip).fireActivateFlipped(window);
				enableFire = false;
				punchSound.play();
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //If A is pressed and hip exists then flip hip and walk to the left
	{
		if (Hip != NULL  && knockbackAmount == 0)
		{
			anim();
			if (flipped == false)
			{
				(*Hip).scale(-1.f, 1.f);
				flipped = true;
			}
			else
			{
				position = position - (*Hip).getSpeed();
				velocity.x = -(*Hip).getSpeed();
			}
		}
	}
	else //If nothing pressed then he isnt moving and no movement needed
	{
		walk = 0;
		velocity.x = 0;
		(*Hip).setTexture(hip_array[15]);
	}
	if ((*Hip).getPosition().y + (*Hip).getGlobalBounds().height < groundHeight || velocity.y < 0) // Ensure if hip in the air that he is falling down
	{
		velocity.y += gravity;
	}
	else //Else hip must be on the floor therefore isnt falling
	{
		(*Hip).setPosition((*Hip).getPosition().x, groundHeight - (*Hip).getGlobalBounds().height); // Problem here
		(*Hip).getHealthBar().setPosition((*Hip).getHealthBar().getPositionX(), groundHeight - 225);
		velocity.y = 0;
		jumpEnabled = true;
	}

	(*Hip).move(velocity.x, velocity.y); //MOve hip in the correct direction
	(*Hip).getHealthBar().move(velocity.x, velocity.y); //Move health bar also
	(*userInterface).move(velocity.x, 0); //MOve user interface as wekk
	if ((*Hip).getPosition().x < 640)
	{
		view.setCenter(640, -140);
	}
	else if ((*Hip).getPosition().x > 4480)//Should be end of level
	{
		view.setCenter(4480, -140);
	}
	else //Everything else
	{
		view.setCenter((*Hip).getPosition().x, -140);
	}
	(*userInterface).setPositionBabyCollected(view.getCenter().x + 600, view.getCenter().y + 300);
	(*userInterface).setPositionScore(view.getCenter().x - 600, view.getCenter().y - 330);
	(*userInterface).setPositionTime(view.getCenter().x + 580, view.getCenter().y - 330);
	window.setView(view); //Set the view
}
//Load images for Hip
void loadHipImages()
{
	babyHipTexture.loadFromFile("baby_hip.png");
	for (int i = 0; i < 21; i++)
	{
		if (!hip_array[i].loadFromFile("hip/hip" + to_string(i + 1) + ".png"))
		{
			// error...
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (!instructions_array[i].loadFromFile("instructions/" + to_string(i + 1) + ".png"))
		{
			// error...
		}
	}
	if (!level2.loadFromFile("level2background.png"))
	{
		// error...
	}
	if (!level3.loadFromFile("level3background.png"))
	{
		// error...
	}
	if (!level4.loadFromFile("londonB.png"))
	{
		// error...
	}
	if (!level5.loadFromFile("volcanoBackground.png"))
	{
		// error...
	}
	if (!level10.loadFromFile("level10background.png"))
	{
		// error...
	}
	if (!texture_2.loadFromFile("desert.jpg"))
	{
		// error...
	}
	if (!pause_texture.loadFromFile("pause.png"))
	{
		// error...
	}
	if (!intro_texture.loadFromFile("intro.png"))
	{
		// error...
	}
	if (!hip_stationary.loadFromFile("hip_still.png"))
	{
		// error...
	}
	if (!game_over.loadFromFile("GameOver.png"))
	{
		// error...
	}
	if (!game_finish.loadFromFile("finish.png"))
	{
		// error...
	}
	if (!quit_game.loadFromFile("quit.png"))
	{
		// error...
	}
	gameOver_sprite.setTexture(game_over);
	Pause_sprite.setTexture(pause_texture);
	intro_sprite.setTexture(intro_texture);
	gameFinish_sprite.setTexture(game_finish);
	quit_sprite.setTexture(quit_game);
}
//Main program loop
int main(){
	float time = 30.f;
	sf::Clock  timer; // To show the elapsed time per frame
	window.setFramerateLimit(60);
	Background.setPosition(0.f, -500.f); //Set background location
	if (loadImages == false)
	{
		loadHipImages(); //Load images of hip
		loadImages = true;
	}
	intro(); //STart the intro screen
	while (window.isOpen()){ //While loop to play the game
		timerClock.restart();
		window.clear();	 //Remove screen contents
		window.draw(Background); //Draw the background 
		if (setUp == false) //If level completed or load for the first time then load level data
		{
			flipped = false;
			gameClock.restart();
			if (!punchSoundBuffer.loadFromFile("punch.wav"))
				printf("error");
			punchSound.setBuffer(punchSoundBuffer);

			if (!hitSoundBuffer.loadFromFile("hit.wav"))
				printf("error");
			hitSound.setBuffer(hitSoundBuffer);

			if (!jumpSoundBuffer.loadFromFile("jump.wav"))
				printf("error");
			jumpSound.setBuffer(jumpSoundBuffer);


			levelComplete = false; //Ensure level is not complete
			if (level == 1) //Level 1
			{
				time = 60.0f;
				if (!music.openFromFile("desert.ogg"))
					printf("ERROR cant load music");// error
				music.play();
				music.setLoop(1);
				Background.setTexture(texture_2);
				//Tile Map for level 1
				int level[height][width] =
				{
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				};
				//Remove previous tile map
				emptyRectangleArrayAndTilesArray();
				//Set up this leve;
				levelSetUp(level);
				// Initialize the view
				view.reset(sf::FloatRect(position, -500, 1280, 720));
				// Apply it
				window.setView(view);
				//Enemy file name
				string filename = "cactus.png";
				//Bullet file name
				string bulletName = "bullet.png";
				//enemy bullet texture loaded
				if (!enemyTexture.loadFromFile(bulletName))
				{
					// error...
				}
				//Load floor texture
				tileTexture.loadFromFile("sand.png");
				//Enemy numbers on the screen
				enemyNumbers = 3;
				//Create first enemy, texture file name, speed, time to move for, X position, Y position, Health, Damage Done (Must be either 25,50,75 or 100), Bullet texture
				enemy = new Enemy(filename, 2, 4, 1600, 40, 25, 25, enemyTexture);
				//Set up the shooting for the enemy, Distance to fire, intervals of time and speed of bullet
				(*enemy).shootingSetUp(200, 2, 3);
				//Set points given for a kill
				enemy->setPointsGiven(100);
				//Store enemy in the enemy array
				enemyArray[0] = enemy;
				//Create second enemy, texture file name, speed, time to move for, X position, Y position, Health, Damage Done (Must be either 25,50,75 or 100), Bullet texture. Repeat above stages
				enemy = new Enemy(filename, 0.2, 2, 3000, -20, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[1] = enemy;
				enemy = new Enemy(filename, 2, 4, 4000, 40, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[2] = enemy;
				//Create the User interface
				userInterface = new UserInterface();
				//Set positions of User Interface Items
				(*userInterface).setPositionScore(0, -500);
				(*userInterface).setPositionTime(screenXSize - 75, -500);
				(*userInterface).setPositionBabyCollected(screenXSize - 75, 175);
				//Set baby collected score
				(*userInterface).setBabyCollected(babyCollected);
				//Create a new PLayer, X Position, Y Position, Speed and Health (Cant be greater than 100 (Leave at 100))
				Hip = new  Player(574, 0, 8, 100);
				//Set there position and texture
				(*Hip).getHealthBar().setPosition(540, (*Hip).getPosition().y - 100);
				(*Hip).setTexture(hip_array[0]);
				(*Hip).setOrigin(64, 64);
				//Create baby hip hop, X position, Y Position and Texture
				babyHipHop = new BabyHipHop(4400, 115, babyHipTexture);
				healthPowerUps = 1;
				//Create a health power up
				healthPowerUp = new HealthPowerUp();
				//Position it
				(*healthPowerUp).setPosition(2000, 117);
				//Set in array
				healthPowerUpArray[0] = healthPowerUp;
				//Say how many speed power ups there will be
				totalSpeedPowerUps = 1;
				//Create speed power up, speed to increase too and time to do this for
				speedPowerUp = new SpeedPowerUp(l12, 5);
				//Set position of the power up
				(*speedPowerUp).setPosition(3500, 117);
				//Add to array
				speedPowerUpArray[0] = speedPowerUp;


				totalDamageIncreasePowerUps = 1;
				damageIncreasePowerUp = new DamageDonePowerUp(15, 5);
				(*damageIncreasePowerUp).setPosition(2320, 53);
				damageIncreasePowerUpArray[0] = damageIncreasePowerUp;



				//Create clocks for the enemy
				for (int i = 0; i < enemyNumbers; i++)
				{
					sf::Clock enemyClock;
					clocks[i] = enemyClock;
				}
				//Finish set up
				setUp = true;
			}
			if (level == 2) //Level 2
			{
				time = 40.0f;
				music.stop();
				if (!music.openFromFile("level_2.ogg"))
					printf("ERROR cant load music");// error
				music.play();
				music.setLoop(1);
				Background.setTexture(level2);
				onGround = true; //Are you on the ground
				//Texture Map
				int level[height][width] =
				{
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				};
				//Tile texture map
				tileTexture.loadFromFile("level2.png");
				//Remove rectangles and floor tiles
				emptyRectangleArrayAndTilesArray();
				//Create the new tile map
				levelSetUp(level);
				// Initialize the view
				view.reset(sf::FloatRect(position, -500, 1280, 720));
				// Apply it
				window.setView(view);
				//Enemy file name
				string filename = "level2enemy.png";
				string filenameb = "level2enemyB.png";
				//Bullet file name
				string bulletName = "bullet.png";
				//Load enemy bullet
				if (!enemyTexture.loadFromFile(bulletName))
				{
					// error...
				}
				//Set up enemies
				enemyNumbers = 4;
				enemy = new Enemy(filenameb, 2, 3, 1450, -280, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[0] = enemy;
				enemy = new Enemy(filename, 0.2, 2, 3000, -20, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[1] = enemy;
				enemy = new Enemy(filename, 2, 4, 4000, 40, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[2] = enemy;
				enemy = new Enemy(filenameb, 1, 3, 875, -280, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[3] = enemy;
				//Set up user interface
				userInterface = new UserInterface();
				(*userInterface).setPositionScore(0, -500);
				(*userInterface).setPositionTime(screenXSize - 75, -500);
				(*userInterface).setPositionBabyCollected(screenXSize - 75, 175);
				(*userInterface).setBabyCollected(babyCollected);
				//Set up player health
				Hip = new  Player(574, 0, 8, 100);
				(*Hip).setPosition(574, 0);
				(*Hip).getHealthBar().setPosition(540, (*Hip).getPosition().y - 100);
				(*Hip).setTexture(hip_array[0]);
				(*Hip).setOrigin(64, 64);
				(*Hip).setScore(score);
				//Set up baby hip hop
				babyHipHop = new BabyHipHop(4400, 115, babyHipTexture);
				//Set up health power ups
				healthPowerUps = 1;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(1600, -180);
				healthPowerUpArray[0] = healthPowerUp;
				//Set up speed power ups
				totalSpeedPowerUps = 1; //number of speed power ups on the screen
				speedPowerUp = new SpeedPowerUp(12, 5);
				(*speedPowerUp).setPosition(3500, 117);
				speedPowerUpArray[0] = speedPowerUp;
				//Enemy clocks
				for (int i = 0; i < enemyNumbers; i++)
				{
					sf::Clock enemyClock;
					clocks[i] = enemyClock;
				}
				setUp = true;
			}
			if (level == 3) //Level 3
			{
				time = 40.0f;
				music.stop();
				if (!music.openFromFile("jungle_music.ogg"))
					printf("ERROR cant load music");// error
				music.play();
				music.setLoop(1);
				Background.setTexture(level3);
				onGround = true; //Are you on the ground
				//Texture Map
				int level[height][width] =
				{
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
					{ 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				};
				//Tile texture map
				tileTexture.loadFromFile("rainforest.png");
				//Remove rectangles and floor tiles
				emptyRectangleArrayAndTilesArray();
				//Create the new tile map
				levelSetUp(level);
				// Initialize the view
				view.reset(sf::FloatRect(position, -500, 1280, 720));
				// Apply it
				window.setView(view);
				//Enemy file name
				string filename = "monkey.png";
				//Bullet file name
				string bulletName = "bullet.png";
				//Load enemy bullet
				if (!enemyTexture.loadFromFile(bulletName))
				{
					// error...
				}
				//Set up enemies
				enemyNumbers = 6;
				enemy = new Enemy(filename, 1, 3, 2400, -280, 30, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[0] = enemy;
				enemy = new Enemy(filename, 1, 5, 3500, -280, 40, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[1] = enemy;
				enemy = new Enemy(filename, 2, 4, 4000, -280, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[2] = enemy;
				enemy = new Enemy(filename, 1, 3, 1000, -216, 30, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[3] = enemy;
				//Set up user interface
				userInterface = new UserInterface();
				(*userInterface).setPositionScore(0, -500);
				(*userInterface).setPositionTime(screenXSize - 75, -500);
				(*userInterface).setPositionBabyCollected(screenXSize - 75, 175);
				(*userInterface).setBabyCollected(babyCollected);
				//Set up player health
				Hip = new  Player(574, 100, 8, 100);
				(*Hip).getHealthBar().setPosition(540, (*Hip).getPosition().y - 100);
				(*Hip).setTexture(hip_array[0]);
				(*Hip).setOrigin(64, 64);
				(*Hip).setScore(score);
				//Set up baby hip hop
				babyHipHop = new BabyHipHop(4400, -196, babyHipTexture);
				//Set up health power ups
				healthPowerUps = 3;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(2450, -211);
				healthPowerUpArray[0] = healthPowerUp;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(3550, -211);
				healthPowerUpArray[1] = healthPowerUp;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(900, 0);
				healthPowerUpArray[2] = healthPowerUp;
				//Set up speed power ups
				totalSpeedPowerUps = 1; //number of speed power ups on the screen
				speedPowerUp = new SpeedPowerUp(12, 5);
				(*speedPowerUp).setPosition(1156, -128);
				speedPowerUpArray[0] = speedPowerUp;
				//Enemy clocks
				for (int i = 0; i < enemyNumbers; i++)
				{
					sf::Clock enemyClock;
					clocks[i] = enemyClock;
				}
				setUp = true;
			}

			if (level == 4) //Level 4
			{
				time = 60.0f;
				music.stop();
				if (!music.openFromFile("national_anthem.ogg"))
					printf("ERROR cant load music");// error
				music.play();
				music.setLoop(1);
				Background.setTexture(level4);
				onGround = true; //Are you on the ground
				//Texture Map
				int level[height][width] =
				{
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				};
				//Tile texture map
				tileTexture.loadFromFile("londontile.png");
				//Remove rectangles and floor tiles
				emptyRectangleArrayAndTilesArray();
				//Create the new tile map
				levelSetUp(level);
				// Initialize the view
				view.reset(sf::FloatRect(position, -500, 1280, 720));
				// Apply it
				window.setView(view);
				//Enemy file name
				string filename = "cameron.png";
				//Bullet file name
				string bulletName = "bullet.png";
				//Load enemy bullet
				if (!enemyTexture.loadFromFile(bulletName))
				{
					// error...
				}
				//Set up enemies
				enemyNumbers = 5;
				enemy = new Enemy(filename, 2, 4, 3400, 40, 25, 25, enemyTexture); // nUMBER 3
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[0] = enemy;
				enemy = new Enemy(filename, 2, 4, 5600, 600, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[1] = enemy;

				enemy = new Enemy(filename, 2, 4, 900, 40, 25, 25, enemyTexture); // NUMBER 1
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[3] = enemy;
				enemy = new Enemy(filename, 2, 4, 2500, -80, 25, 25, enemyTexture); // number 2
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[4] = enemy;
				//Set up user interface
				userInterface = new UserInterface();
				(*userInterface).setPositionScore(0, -500);
				(*userInterface).setPositionTime(screenXSize - 75, -500);
				(*userInterface).setPositionBabyCollected(screenXSize - 75, 175);
				(*userInterface).setBabyCollected(babyCollected);
				//Set up player health
				Hip = new  Player(574, 0, 8, 100);
				(*Hip).getHealthBar().setPosition(540, (*Hip).getPosition().y - 100);
				(*Hip).setTexture(hip_array[0]);
				(*Hip).setOrigin(64, 64);
				(*Hip).setScore(score);
				//Set up baby hip hop
				babyHipHop = new BabyHipHop(4400, 115, babyHipTexture);
				//Set up health power ups
				healthPowerUps = 3;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(800, 1000);
				healthPowerUpArray[0] = healthPowerUp;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(3000, -135);
				healthPowerUpArray[1] = healthPowerUp;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(2900, -135);
				healthPowerUpArray[2] = healthPowerUp;
				//Set up speed power ups
				totalSpeedPowerUps = 1; //number of speed power ups on the screen
				speedPowerUp = new SpeedPowerUp(12, 5);
				(*speedPowerUp).setPosition(1700, -90);
				speedPowerUpArray[0] = speedPowerUp;
				//Enemy clocks
				for (int i = 0; i < enemyNumbers; i++)
				{
					sf::Clock enemyClock;
					clocks[i] = enemyClock;
				}
				setUp = true;
			}
			if (level == 5) //Level 
			{
				time = 45.0f;
				music.stop();
				if (!music.openFromFile("Volcano.ogg"))
					printf("ERROR cant load music");// error
				music.play();
				music.setLoop(1);
				Background.setTexture(level5);
				onGround = true; //Are you on the ground
				//Texture Map
				int level[height][width] =
				{

					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				};
				//Tile texture map
				tileTexture.loadFromFile("LavaTile.png");
				//Remove rectangles and floor tiles
				emptyRectangleArrayAndTilesArray();
				//Create the new tile map
				levelSetUp(level);
				// Initialize the view
				view.reset(sf::FloatRect(position, -500, 1280, 720));
				// Apply it
				window.setView(view);
				//Enemy file name
				string filename = "volcanoEnemy.png";
				//Bullet file name
				string bulletName = "volcanoBullet.png";
				//Load enemy bullet
				if (!enemyTexture.loadFromFile(bulletName))
				{
					// error...
				}
				//Set up enemies
				enemyNumbers = 6;
				enemy = new Enemy(filename, 1, 2, 1088, -300, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[0] = enemy;
				enemy = new Enemy(filename, 0.1, 2, 1536, -364, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[1] = enemy;
				enemy = new Enemy(filename, 0.1, 2, 1728, -364, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[2] = enemy;
				enemy = new Enemy(filename, 0.5, 2, 3500, -300, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[3] = enemy;
				enemy = new Enemy(filename, 1, 2, 4256, -108, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[4] = enemy;
				//Set up user interface
				userInterface = new UserInterface();
				(*userInterface).setPositionScore(0, -500);
				(*userInterface).setPositionTime(screenXSize - 75, -500);
				(*userInterface).setPositionBabyCollected(screenXSize - 75, 175);
				(*userInterface).setBabyCollected(babyCollected);
				//Set up player health
				Hip = new  Player(574, 0, 8, 100);
				(*Hip).getHealthBar().setPosition(540, (*Hip).getPosition().y - 100);
				(*Hip).setTexture(hip_array[0]);
				(*Hip).setOrigin(64, 64);
				(*Hip).setScore(score);
				//Set up baby hip hop
				babyHipHop = new BabyHipHop(4400, 115, babyHipTexture);
				//Set up health power ups
				healthPowerUps = 3;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(1100, -260);
				healthPowerUpArray[0] = healthPowerUp;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(4325, -68);
				healthPowerUpArray[1] = healthPowerUp;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(1728, -324);
				healthPowerUpArray[2] = healthPowerUp;
				//Set up speed power ups
				totalSpeedPowerUps = 1; //number of speed power ups on the screen
				speedPowerUp = new SpeedPowerUp(12, 5);
				(*speedPowerUp).setPosition(1258, -260);
				speedPowerUpArray[0] = speedPowerUp;
				//Enemy clocks
				for (int i = 0; i < enemyNumbers; i++)
				{
					sf::Clock enemyClock;
					clocks[i] = enemyClock;
				}
				setUp = true;
			}

			if (level == 6) //Level 10
			{
				time = 60.0f;
				music.stop();
				if (!music.openFromFile("level_10.ogg"))
					printf("ERROR cant load music");// error
				music.play();
				music.setLoop(1);
				Background.setTexture(level10);
				onGround = true; //Are you on the ground
				//Texture Map
				int level[height][width] =
				{

					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
					{ 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				};
				//Tile texture map
				tileTexture.loadFromFile("level10.png");
				//Remove rectangles and floor tiles
				emptyRectangleArrayAndTilesArray();
				//Create the new tile map
				levelSetUp(level);
				// Initialize the view
				view.reset(sf::FloatRect(position, -500, 1280, 720));
				// Apply it
				window.setView(view);
				//Enemy file name
				string filename = "level10enemy.png";
				//Bullet file name
				string bulletName = "whole_egg.png";
				//Load enemy bullet
				if (!enemyTexture.loadFromFile(bulletName))
				{
					// error...
				}
				//Set up enemies
				enemyNumbers = 6;
				enemy = new Enemy(filename, 2, 4, 1600, 40, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[0] = enemy;
				enemy = new Enemy(filename, 0.2, 2, 3000, -300, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[1] = enemy;
				enemy = new Enemy(filename, 2, 4, 4000, -500, 25, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[2] = enemy;
				enemy = new Enemy(filename, 2, 4, 800, 50, 15, 25, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[3] = enemy;
				enemy = new Enemy("boss.png", 2, 6, 3500, -90, 100, 100, enemyTexture);
				(*enemy).shootingSetUp(200, 1, 10);
				enemy->setPointsGiven(100);
				enemyArray[4] = enemy;
				enemy = new Enemy(filename, 2, 4, 900, -200, 15, 100, enemyTexture);
				(*enemy).shootingSetUp(200, 2, 3);
				enemy->setPointsGiven(100);
				enemyArray[5] = enemy;

				//Set up user interface
				userInterface = new UserInterface();
				(*userInterface).setPositionScore(0, -500);
				(*userInterface).setPositionTime(screenXSize - 75, -500);
				(*userInterface).setPositionBabyCollected(screenXSize - 75, 175);
				(*userInterface).setBabyCollected(babyCollected);
				//Set up player health
				Hip = new  Player(574, 0, 8, 100);
				(*Hip).getHealthBar().setPosition(540, (*Hip).getPosition().y - 100);
				(*Hip).setTexture(hip_array[0]);
				(*Hip).setOrigin(64, 64);
				(*Hip).setScore(score);
				//Set up baby hip hop
				babyHipHop = new BabyHipHop(4400, 115, babyHipTexture);
				//Set up health power ups
				healthPowerUps = 2;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(2000, 117);
				healthPowerUpArray[0] = healthPowerUp;
				healthPowerUp = new HealthPowerUp();
				(*healthPowerUp).setPosition(1000, 117);
				healthPowerUpArray[1] = healthPowerUp;
				//Set up speed power ups
				totalSpeedPowerUps = 1; //number of speed power ups on the screen
				speedPowerUp = new SpeedPowerUp(12, 5);
				(*speedPowerUp).setPosition(3500, 117);
				speedPowerUpArray[0] = speedPowerUp;
				//Enemy clocks
				for (int i = 0; i < enemyNumbers; i++)
				{
					sf::Clock enemyClock;
					clocks[i] = enemyClock;
				}
				setUp = true;
			}
		}
		//Test if window closed
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//If escape pressed then pause the game 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.clear();
			view.reset(sf::FloatRect(0, 0, 1280, 720));
			window.setView(view);
			pause();
			view.reset(sf::FloatRect(position, -500, 1280, 720));
			window.setView(view);
		}
		timer.restart();
		// If Hip exists
		if (Hip != NULL)
		{
			//Detect what you hit on the map
			levelCollisionDetection();
			//Detect if moved
			movement();
			//Draw heatlh bar
			(*Hip).getHealthBar().draw(window);
			//Draw Player
			PlayerDraw((*Hip));
			//If hip firing
			if ((*Hip).getFireActivated() == true)
			{
				//For every enemy check if they have been hit
				for (int i = 0; i < enemyNumbers; i++)
				{
					if (enemyArray[i] != NULL)
					{
						playerFireCollision((*Hip), (*enemyArray[i]));
					}
				}
				//Move the bullet of Hip
				(*Hip).moveBullet((*Hip).getFlippedShooting());
				//Draw the bullet of Hip
				(*Hip).drawBullets(window);
				//Detect whether the bullet is off screen
				bulletOffScreenDetection((*Hip));
				//For every enemy, if they exist and there health becomes less than 0 then kill them, store there bullets if firing though
				for (int i = 0; i < enemyNumbers; i++)
				{
					if (enemyArray[i] != NULL)
					{
						if ((*enemyArray[i]).getHealth() <= 0)
						{
							(*Hip).setScore((*enemyArray[i]).getPointsGiven() + (*Hip).getScore());
							cout << (*Hip).getScore() << " Score" << "\n";
							cout << "0 Reached" << "\n";
							if ((*enemyArray[i]).getFireActivated() == true) // Get bullet if activated and enemy dead
							{
								deadEnemyBullets.push_back((*enemyArray[i]).getBullet());
							}
							delete enemyArray[i];
							enemyArray[i] = NULL;
							enemyDead = true;
						}
					}
				}
			}
			//Fire dead enemy bullets
			deadEnemyBulletsFire((*Hip));
			//For all enemies, Move them, Fire bullet and detect whether hit Hip
			for (int i = 0; i < enemyNumbers; i++)
			{
				if (enemyArray[i] != NULL)
				{
					AIMove((*enemyArray[i]), clocks[i]);
					AIFire((*enemyArray[i]), clocks[i], (*Hip));
					DetectHitSprite((*Hip), (*enemyArray[i]));
					//Detect whether dead enemy bullet hit Hip
					deadEnemyBulletHitDetect((*Hip));
					//Draw enemies health bar
					(*enemyArray[i]).getHealthBar().drawHealthBar(window);
					//Detect whether play hits enemy
					playerHitSpriteDetection((*Hip), (*enemyArray[i]));
					//If player hit enemy on top then kill it
					if (hitEnemyOnTop == true)
					{
						(*Hip).setScore((*enemyArray[i]).getPointsGiven() + (*Hip).getScore());
						cout << (*Hip).getScore() << " Score" << "\n";
						delete enemyArray[i];
						enemyArray[i] = NULL;
						enemyDead = true;
					}
					//Detect whether Hip is below the floor
					belowFloorDetection((*Hip));
					//If Hip has health below 0 then kill him
					if ((*Hip).getHealth() <= 0 && godMode == false)
					{
						delete Hip;
						Hip = NULL;
						break;
					}
				}
			}
		}
		//If hip still alive then check for power ups and check if collided with them and delete them if have.
		if (Hip != NULL)
		{
			for (int i = 0; i < healthPowerUps; i++)
			{
				if (healthPowerUpArray[i] != NULL)
				{
					window.draw((*healthPowerUpArray[i]));
					if (intersectHealthPowerUp((*Hip), (*healthPowerUpArray[i])))
					{
						delete healthPowerUpArray[i];
						healthPowerUpArray[i] = NULL;
					}
				}
			}
			for (int i = 0; i < totalSpeedPowerUps; i++)
			{
				if (speedPowerUpArray[i] != NULL)
				{
					window.draw((*speedPowerUpArray[i]));
					if (intersectSpeedPowerUp((*Hip), (*speedPowerUpArray[i])))
					{
						delete speedPowerUpArray[i];
						speedPowerUpArray[i] = NULL;
					}
				}
			}
			for (int i = 0; i < totalDamageIncreasePowerUps; i++)
			{
				if (damageIncreasePowerUpArray[i] != NULL)
				{
					window.draw((*damageIncreasePowerUpArray[i]));
					if (intersectDamageIncreasePowerUp((*Hip), (*damageIncreasePowerUpArray[i])))
					{
						delete damageIncreasePowerUpArray[i];
						damageIncreasePowerUpArray[i] = NULL;
					}
				}
			}
			//Set to original speed up power up time bonus up
			if (speedPowerUpTimeRemainig == 0)
			{
				(*Hip).setSpeed((*Hip).getOriginalSpeed());
				speedPowerUpTimeRemainig = -1;
			}
			//Set to original Damage done prior to power up
			if (damageIncreaseTimeRemaining == 0)
			{
				(*Hip).setDamageDone((*Hip).getOriginalDamageDone());
				damageIncreaseTimeRemaining = -1;
			}
			//Draw hips health bar
			(*Hip).getHealthBar().draw(window);
			//Draw hip
			PlayerDraw((*Hip));
			//If user interface exists then set score and time and draw it
			if (userInterface != NULL)
			{
				(*userInterface).setScore(std::to_string((*Hip).getScore()));
				(*userInterface).setTime(std::to_string((int)time));
				(*userInterface).draw(window);
			}
		}
		//If hip dead then game over
		if (Hip == NULL || gameFinished == true)
		{
			//Reset all Global Variables to initial state
			secondsBeen.clear();
			setUp = false;
			walk = 0; //Controls Hip images
			esc_press = false; //Checks if escape has been pressed
			position = 0; //Controls camera position 
			setUp = false; //Checks to see if level loaded
			flipped = false; //Checks position of Hip
			stepsSpeed = 0;
			enemyDead = false; //Checks if enemy dead
			enableFire = false; //Can the player fire
			jumpSpeed = 10.0f; //Speed of jump
			groundHeight = 500; //Level ground at
			maxHeight = -50; //Max height to jump
			jumpEnabled = true; //Can you jump
			hitEnemyOnTop = false; //Did you hit an enemy on top
			speedPowerUpTimeRemainig = -1; //Time left for powerups
			onGround = true; //Are you on the ground
			onBox = true; //are you in the air on a box
			levelComplete = false; //Is the level complete
			Hip = NULL;
			cout << "Game Over" << "\n";
			window.clear();
			view.reset(sf::FloatRect(0, 0, 1280, 720));
			window.setView(view);
			cout << gameFinished << "\n";
			bool done = false;
			if (gameFinished == true)
			{

				window.draw(gameFinish_sprite);
				window.display();
				while (1)
				{
					sf::sleep(sf::milliseconds(10));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
					{
						done = true;
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
					{
						exit(0);
					}
					if (done == true && !(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)))
					{
						setUp = false;
						gameFinished = false;
						level = 1;
						main();
					}
				}
			}
			if (gameFinished == false)
			{
				window.draw(gameOver_sprite);


				window.display();
				while (1)
				{
					sf::sleep(sf::milliseconds(10));
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
					{
						done = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
					{
						quit();
						done = true;
						//main();
					}
					if (done == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && !sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
					{
						setUp = false;
						main();
					}
				}
			}


		}
		//If time at certain point then enable fire and reduce speed power up time remaining
		if (((int)gameClock.getElapsedTime().asSeconds() % 1) == 0 && hasSecondBeen((int)gameClock.getElapsedTime().asSeconds()) == false)
		{
			enableFire = true;
			if (speedPowerUpTimeRemainig > 0)
			{
				speedPowerUpTimeRemainig = speedPowerUpTimeRemainig - 1;
			}
			if (damageIncreaseTimeRemaining > 0)
			{
				damageIncreaseTimeRemaining = damageIncreaseTimeRemaining - 1;
			}
			secondsBeen.push_back((int)gameClock.getElapsedTime().asSeconds());
		}
		if (Hip != NULL)
		{
			//Detect whether hit baby
			hitBaby((*babyHipHop));
			window.draw((*babyHipHop));
		}
		window.display();
		// Decrease time by amount of time taken to do this frame
		time -= timer.getElapsedTime().asSeconds();
		//If time is 0 then kill Hip
		if ((int)time == 0)
		{
			Hip = NULL;
		}
	}
}



