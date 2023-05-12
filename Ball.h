#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "brick.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Ball
{
private:
	sf::CircleShape shape;
	sf::Vector2f oldPosition;
	sf::Vector2f position;
	float speed;
	int radius;
	sf::Vector2f direction;
	int lives;
	static bool isRandInitialized;
	double randomizeAngle();
	Ball();
	void setAngle(double angle);
public:
	Ball(int x, int y, int radius, float speed);
	~Ball();
	void move(float ellapsedTime);
	void draw(sf::RenderWindow& window);
	sf::SoundBuffer collisionSoundBuffer;
	sf::Sound collisionSound;
	float getSpeed();
	void setSpeed(float newSpeed);
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getPosition();
	void setDirection(sf::Vector2f newDirection);
	void manageCollisionWith(sf::RenderWindow& window);
	void manageCollisionWith(Player& player);
	void manageCollisionWith(Brick* brick);
};