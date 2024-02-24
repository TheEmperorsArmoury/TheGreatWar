#include "TheGreatWar.h"

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

        TheGreatWar::SpawnRect(sf::Vector2f(100, 100), sf::Vector2f(window.getSize().x, window.getSize().y / 2), sf::Color::Red, sf::Color::Red, window);
        TheGreatWar::SpawnRect(sf::Vector2f(50, 100), sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Color::Transparent, sf::Color::Blue, window);
        
        int numYellowSquares = 5;  
        sf::RectangleShape yellowSquare(sf::Vector2f(20, 20));
        yellowSquare.setPosition(0, window.getSize().y / 2 - yellowSquare.getSize().y);
        yellowSquare.setFillColor(sf::Color::Yellow);
        for (int i = 0; i < numYellowSquares; i++) {
            window.draw(yellowSquare);
            yellowSquare.move(0, yellowSquare.getSize().y + 10);
        }

        // Building navmesh
        TheGreatWar::InitializeNavMesh();

        


        window.display();
    }

    return 0;
}

void TheGreatWar::SpawnRect(sf::Vector2f dimensions, sf::Vector2f position, sf::Color color, sf::Color outlineColor, sf::RenderWindow& window, int outlineThickness)
{
    sf::RectangleShape tempSquare(sf::Vector2f(dimensions.x, dimensions.y));
    tempSquare.setPosition(position.x - tempSquare.getSize().x / 2, position.y - tempSquare.getSize().y / 2);
    tempSquare.setFillColor(color);
    tempSquare.setOutlineThickness(outlineThickness);
    tempSquare.setOutlineColor(outlineColor);
    window.draw(tempSquare);
}

void TheGreatWar::InitializeNavMesh()
{
    // 2D array to initialize grid
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 20; y++)
        {
            TheGreatWar::SpawnRect(sf::Vector2f(m_CellSize, m_CellSize), sf::Vector2f(x * m_CellSize, y * m_CellSize), sf::Color::Transparent, sf::Color::White, window, 1);
        }
    }

}


