#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include <SFML/Graphics.hpp>

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

        sf::RectangleShape redSquare(sf::Vector2f(100, 100)); 
        redSquare.setPosition(window.getSize().x - redSquare.getSize().x,
            window.getSize().y / 2 - redSquare.getSize().y / 2);
        redSquare.setFillColor(sf::Color::Red);
        window.draw(redSquare);


        sf::RectangleShape blueRectangle(sf::Vector2f(50, 100));
        blueRectangle.setPosition(window.getSize().x / 2 - blueRectangle.getSize().x / 2,
            window.getSize().y / 2 - blueRectangle.getSize().y / 2);
        blueRectangle.setFillColor(sf::Color::Blue);
        window.draw(blueRectangle);


        int numYellowSquares = 5;  
        sf::RectangleShape yellowSquare(sf::Vector2f(20, 20));
        yellowSquare.setPosition(0, window.getSize().y / 2 - yellowSquare.getSize().y);
        yellowSquare.setFillColor(sf::Color::Yellow);
        for (int i = 0; i < numYellowSquares; i++) {
            window.draw(yellowSquare);
            yellowSquare.move(0, yellowSquare.getSize().y + 5);
        }

        window.display();
    }

    return 0;
}