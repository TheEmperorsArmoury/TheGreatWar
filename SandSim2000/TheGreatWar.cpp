#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include <SFML/Graphics.hpp>


static void SpawnRect(sf::Vector2f dimensions, sf::Vector2f position, sf::Color color, sf::RenderWindow& window, int outlineThickness = 5)
{
    sf::RectangleShape tempSquare(sf::Vector2f(dimensions.x, dimensions.y));
    tempSquare.setPosition(position.x - tempSquare.getSize().x / 2, position.y - tempSquare.getSize().y / 2);
    tempSquare.setFillColor(color);
    window.draw(tempSquare);
}


int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "AI Test Window", sf::Style::Fullscreen);

    


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);




        SpawnRect(sf::Vector2f(100, 100), sf::Vector2f(window.getSize().x, window.getSize().y / 2), sf::Color::Red, window);
        SpawnRect(sf::Vector2f(50, 100), sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Color::Blue, window);


        int numYellowSquares = 5;  
        sf::RectangleShape yellowSquare(sf::Vector2f(20, 20));
        yellowSquare.setPosition(0, window.getSize().y / 2 - yellowSquare.getSize().y);
        yellowSquare.setFillColor(sf::Color::Yellow);
        for (int i = 0; i < numYellowSquares; i++) {
            window.draw(yellowSquare);
            yellowSquare.move(0, yellowSquare.getSize().y + 10);
        }

        window.display();
    }

    return 0;
}


