#include "Ball.h"

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
	// Si la balle sort de l'écran (par en haut)
	if (position.y <= 0)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
		position.y = 0;
	}
	else if (position.y + 2 * radius >= window.getSize().y)
	{
		direction.y *= -1;
		position.y = window.getSize().y - 2 * radius;
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
	// Vérifier s'il y a collision entre la balle et la plateforme
	if (position.x + radius >= player.getPosition().x && position.x - radius <= player.getPosition().x + player.getSize().x && position.y + radius >= player.getPosition().y && position.y - radius <= player.getPosition().y + player.getSize().y)
	{
		// Calculer l'angle de rebond en fonction de la position de la collision sur la plateforme
		double angle = ((position.x - player.getPosition().x) / player.getSize().x) * (5 * 30 / 12) - (5 * 30 / 12) / 2;

		// Changer la direction de la balle en fonction de l'angle de rebond
		setAngle(angle);
	}
}

void Ball::manageCollisionWith(Brick* brick)
{
	sf::FloatRect ballBounds = shape.getGlobalBounds();
	sf::FloatRect brickBounds = brick->getShape().getGlobalBounds();
	// Vérifie si la balle touche la brique
	if (ballBounds.intersects(brickBounds))
	{
		// Calcule la position relative de la balle par rapport à la brique
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

		// Réduit la santé de la brique et change sa couleur
		brick->hit();

		// Changer la direction de la balle immédiatement après la collision
		// en fonction de la position de la brique relative à la balle
		if (intersectX > 0)
		{
			// La balle touche la brique sur le côté droit
			direction.x = std::abs(direction.x);
		}
		else
		{
			// La balle touche la brique sur le côté gauche
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
