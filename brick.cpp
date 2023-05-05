#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, int health)
{
    this->position = sf::Vector2f(x, y);
    this->size = sf::Vector2f(width, height);
    this->health = health;
    this->shape.setSize(size);
    this->shape.setPosition(position);
}

Brick::~Brick()
{
}

void Brick::draw(sf::RenderWindow& window)
{
    if (isAlive()) {
        window.draw(shape);
    }
}

sf::Color Brick::getColorFromLife()
{
    // Utilise la santé pour déterminer la couleur de la brique
    if (health == 3) {
        return sf::Color::Red;
    }
    else if (health == 2) {
        return sf::Color::Yellow;
    }
    else if (health == 1) {
        return sf::Color::Green;
    }
    else {
        return sf::Color::Transparent;
    }
}

bool Brick::isAlive()
{
    return health > 0;
}

void Brick::hit()
{
    health--;
}

sf::Vector2f Brick::getPosition()
{
    return position;
}

sf::Vector2f Brick::getSize()
{
    return size;
}