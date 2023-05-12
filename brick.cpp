#include "Brick.h"
#include <iostream>

Brick::Brick(int x, int y, int width, int height, int health)
{
	// Initialisation des membres de la classe
	this->position = sf::Vector2f(x, y);
	this->size = sf::Vector2f(width, height);
	this->shape = sf::RectangleShape(size);
	this->health = health;
	shape.setFillColor(sf::Color::Green); // Couleur initiale est vert
	this->shape.setOutlineColor(sf::Color::White); // Blanc
	this->shape.setOutlineThickness(1); // Largeur de 1 pixel pour le contour
	this->lastCollisionTime = 0; // Initialisation du temps de la derni�re collision � z�ro
	// Charger le fichier audio de collision
	
	//if (!collisionSoundBuffer.loadFromFile("pan.wav"))
	if (!collisionSoundBuffer.loadFromFile("pet.wav"))
	{
		// �chec du chargement
		std::cout << "Erreur : impossible de charger le fichier audio de collision" << std::endl;
	}
	collisionSound.setBuffer(collisionSoundBuffer);
}

Brick::~Brick()
{
	// Destructeur vide car la classe ne g�re pas de ressources dynamiques
}

void Brick::draw(sf::RenderWindow& window)
{
	if (isAlive())
	{
		// Si la brique est encore en vie, dessiner la forme sur la fen�tre donn�e
		shape.setPosition(position);
		window.draw(shape);
	}
}

bool Brick::isAlive()
{
	// Renvoyer true si la brique a une sant� sup�rieure � z�ro, sinon false
	return health > 0;
}

void Brick::destroyAndDelete(std::deque<Brick*>& bricks)
{
	// Retirer la brique de la deque de briques
	bricks.erase(std::remove(bricks.begin(), bricks.end(), this), bricks.end());
	// Supprimer l'objet de la m�moire
	delete this;
}

void Brick::hit()
{
	if (isAlive())
	{
		// Si la brique est encore en vie et si le temps depuis la derni�re collision est sup�rieur ou �gal � une seconde,
		// r�duire sa sant�, changer sa couleur et mettre � jour le temps de la derni�re collision
		if (clock.getElapsedTime().asSeconds() - lastCollisionTime >= 0.1) {
			health--;
			setColor();
			lastCollisionTime = clock.getElapsedTime().asSeconds();
			// Jouer le son de collision
			collisionSound.play();
		}
	}
}


sf::Vector2f Brick::getPosition()
{
	// Renvoyer la position de la brique
	return position;
}

sf::RectangleShape Brick::getShape()
{
	// Renvoyer la forme de la brique
	return shape;
}

sf::Vector2f Brick::getSize()
{
	// Renvoyer la taille de la brique
	return size;
}

void Brick::setColor()
{
	this->shape.setOutlineColor(sf::Color::White); // Blanc
	this->shape.setOutlineThickness(1); // Largeur de 1 pixel pour le contour
	if (this->health == 2)
	{
		// Si la sant� est de 2, changer la couleur � orange
		this->shape.setFillColor(sf::Color(255, 165, 0)); // Orange
	}
	else if (this->health == 1)
	{
		// Si la sant� est de 1, changer la couleur � rouge
		this->shape.setFillColor(sf::Color::Red); // Rouge
	}
}

bool Brick::operator==(const Brick& other) const
{
	// Renvoyer true si cette brique est la m�me que l'autre brique, sinon false
	return this == &other;
}