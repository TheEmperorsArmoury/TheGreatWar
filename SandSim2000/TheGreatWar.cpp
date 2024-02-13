#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include <SFML/Graphics.hpp>

//Test

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "AI Test Window");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        sf::RectangleShape rectangle(sf::Vector2f(100, 50));
        rectangle.setPosition(sf::Vector2f(200, 150));
        rectangle.setFillColor(sf::Color::Red);
        window.draw(rectangle);

        sf::RectangleShape rectangle2(sf::Vector2f(50, 100));
        rectangle2.setPosition(sf::Vector2f(400, 250));
        rectangle2.setFillColor(sf::Color::Red);
        window.draw(rectangle2);

        window.display();
    }

    return 0;
}