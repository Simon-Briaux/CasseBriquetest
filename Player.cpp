#include "player.h"



Player::Player(int y, int width, int height)

{
	this->y = y;
	position = sf::Vector2f(0, y);
	size = sf::Vector2f(width, height);
	shape.setSize(size);
	shape.setFillColor(sf::Color::White);
}

Player::~Player()
{

}

void Player::draw(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Get the current mouse position
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Calculate the new position of the player
        float newX = mousePosition.x - (size.x / 2); // center the player on the mouse position
        newX = std::max(newX, 0.0f); // keep the player inside the left border of the window
        newX = std::min(newX, window.getSize().x - size.x); // keep the player inside the right border of the window
        position.x = newX;
    }

    // Set the player shape's position and draw it
    shape.setPosition(position);
    window.draw(shape);
}

sf::RectangleShape Player::getShape()
{
	return shape;
}

sf::Vector2f Player::getPosition()
{
	return position;
}

sf::Vector2f Player::getSize()
{
	return size;
}

