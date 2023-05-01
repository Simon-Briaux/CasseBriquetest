#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Brick.h"
#include <iostream>
#include <deque>

double mapValue(double value, double min, double max, double nMin, double nMax)
{
    // Y = (X-A)/(B-A) * (D-C) + C
    double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
    return newVal;
}

int main(int argc, char** argv)
{
    const int NUM_ROWS = 5;
    const int NUM_COLS = 10;
    const int BRICK_WIDTH = 50;
    const int BRICK_HEIGHT = 20;
    const int BRICK_MARGIN = 5;

    std::deque<Brick*> bricks;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int x = j * (BRICK_WIDTH + BRICK_MARGIN);
            int y = i * (BRICK_HEIGHT + BRICK_MARGIN);
            Brick* brick = new Brick(x, y, BRICK_WIDTH, BRICK_HEIGHT, 3);
            bricks.push_back(brick);
        }
    }

    Ball ball(200, 250, 10, 200);
    Player player(550, 100, 10);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Casse Brique");

    sf::RectangleShape rdr2;
    rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Clock clock;
    float ellapsedTime = 0;

    // on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
    while (window.isOpen())
    {
        ellapsedTime = clock.restart().asSeconds();
        // on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
        sf::Event event;
        while (window.pollEvent(event))
        {
            // �v�nement "fermeture demand�e" : on ferme la fen�tre
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ball.move(ellapsedTime);
        ball.manageCollisionWith(window);

        window.clear();

        // Dessin des briques
        for (int i = 0; i < bricks.size(); i++) {
            bricks[i]->draw(window);
        }

        double mappedValue = mapValue(ball.getPosition().x, 0, window.getSize().x, 0, 255);
        double mappedValue2 = mapValue(ball.getPosition().y, 0, window.getSize().y, 0, 255);
        double mappedValue3 = (mappedValue + mappedValue2) / 2.0;
        rdr2.setFillColor(sf::Color(mappedValue, 255 - mappedValue2, mappedValue3));

        rdr2.setPosition(0, 0);
        window.draw(rdr2);
        player.draw(window);
        ball.draw(window);
        window.display();
    }

    // Nettoyage des briques
    for (int i = 0; i < bricks.size(); i++) {
        delete bricks[i];
    }
    bricks.clear();

    return 0;
}
