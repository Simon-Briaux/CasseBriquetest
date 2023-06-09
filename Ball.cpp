#include "Ball.h"
#include <cmath>
#include <iostream>

const double PI = std::acos(-1); // alternative � M_PI

double radius = 10.0;
double circumference = 2.0 * PI * radius;


bool Ball::isRandInitialized = false;

double Ball::randomizeAngle()
{
	if (!isRandInitialized)
	{
		srand(time(NULL));
		isRandInitialized = true;
	}

	return (((double)rand() / (double)RAND_MAX) * 60.0) - 30.0;
}

void Ball::setAngle(double angle)
{
	direction.x = sin(angle);
	direction.y = -cos(angle);
}

Ball::Ball(int x, int y, int radius, float speed)
{
	position.x = x;
	position.y = y;
	oldPosition = position;
	shape.setFillColor(sf::Color(sf::Color::White));
	shape.setPosition(position);
	this->radius = radius;
	shape.setRadius(radius);
	this->speed = speed;

	setAngle(randomizeAngle());
}

Ball::~Ball()
{
}

void Ball::move(float ellapsedTime)
{
	position += ellapsedTime * speed * direction;
}

void Ball::draw(sf::RenderWindow& window)
{
	shape.setPosition(position);
	window.draw(shape);
}


float Ball::getSpeed()
{
	return speed;
}

void Ball::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Ball::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
}

sf::Vector2f Ball::getPosition()
{
	return position;
}

void Ball::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void Ball::manageCollisionWith(sf::RenderWindow& window)
{
	// Si la balle sort de l'�cran (par en haut)
	if (position.y <= 0)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
		position.y = 0;
	}

	if (position.x <= 0)
	{
		direction.x *= -1;
		position.x = 0;
	}
	else if (position.x + 2 * radius >= window.getSize().x)
	{
		direction.x *= -1;
		position.x = window.getSize().x - 2 * radius;
	}
}

void Ball::manageCollisionWith(Player& player)
{
	// V�rifier s'il y a collision entre la balle et la plateforme
	if (position.x + radius >= player.getPosition().x && position.x - radius <= player.getPosition().x + player.getSize().x && position.y + radius >= player.getPosition().y && position.y - radius <= player.getPosition().y + player.getSize().y)
	{
		double paddleCenter = player.getPosition().x + player.getSize().x / 2.0;
		double collisionOffset = position.x - paddleCenter;
		double maxOffset = player.getSize().x / 2.0 + radius;
		double normalizedOffset = collisionOffset / maxOffset;
		double angle = normalizedOffset * (5 * PI / 12.0);

		if (direction.y > 0)
		{
			// La balle est en collision avec le haut de la plateforme
			position.y = player.getPosition().y - radius;
		}
		else
		{
			// La balle est en collision avec le bas de la plateforme
			position.y = player.getPosition().y + player.getSize().y + radius;
		}
		direction.y *= -1;

		// Changer la direction de la balle en fonction de l'angle de rebond
		setAngle(angle);

		// Met � jour la position pr�c�dente de la balle pour �viter qu'elle traverse la plateforme � la prochaine it�ration
		oldPosition = position;
	}
}


void Ball::manageCollisionWith(Brick* brick)
{
	sf::FloatRect ballBounds = shape.getGlobalBounds();
	sf::FloatRect brickBounds = brick->getShape().getGlobalBounds();
	// V�rifie si la balle touche la brique
	if (ballBounds.intersects(brickBounds))
	{
		// Calcule la position relative de la balle par rapport � la brique
		double intersectX = position.x + radius - brick->getPosition().x;
		double intersectY = position.y + radius - brick->getPosition().y;
		double deltaX = brick->getSize().x / 2.0 - std::abs(intersectX);
		double deltaY = brick->getSize().y / 2.0 - std::abs(intersectY);

		// Inverse la direction de la balle en fonction de l'axe de la collision
		if (deltaX > deltaY)
		{
			// Collision horizontale
			direction.x *= -1;
		}
		else
		{
			// Collision verticale
			direction.y *= -1;
		}

		// R�duit la sant� de la brique et change sa couleur
		brick->hit();

		// Changer la direction de la balle imm�diatement apr�s la collision
		// en fonction de la position de la brique relative � la balle
		if (intersectX > 0)
		{
			// La balle touche la brique sur le c�t� droit
			direction.x = std::abs(direction.x);
		}
		else
		{
			// La balle touche la brique sur le c�t� gauche
			direction.x = -std::abs(direction.x);
		}

		if (intersectY > 0)
		{
			// La balle touche la brique en bas
			direction.y = std::abs(direction.y);
		}
		else
		{
			// La balle touche la brique en haut
			direction.y = -std::abs(direction.y);


		}
	}

}

