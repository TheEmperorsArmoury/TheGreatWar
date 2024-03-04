#include <SFML/Graphics.hpp>
#include <queue>
#include <set>
#include <iostream>

const int rows = 10;
const int cols = 10;
const int border = 10;
const int cellSize = 80;
const int cellBorderWidth = 4;

const std::vector<int> startingPos = { 6, 6 };
const std::vector<int> endingPos = { 7, 7 };

struct Cell {
    sf::Vector2i position;
    bool impassableTerrain;
    std::shared_ptr<sf::RectangleShape> shape;
};

struct Node {
    int x, y;
    int gScore;
    int hScore;
    int fScore;
    Node* parent;
    bool isInPath;

    Node(int _x, int _y) : x(_x), y(_y), gScore(0), hScore(0), fScore(0), parent(nullptr), isInPath(false) {}
};

void VectorFieldPathfinding(const Node& start, const Node& goal, const Cell grid[][cols]) {

}

sf::Vector2f getScreenPositionFromGridCoordinate(int x, int y, int cellSize) {
    if (x < 0 || x >= cols || y < 0 || y >= rows) {
        return sf::Vector2f(-1.0f, -1.0f);
    }

    float xPos = x * cellSize + border;
    float yPos = y * cellSize + border;

    float xOffset = (cellSize - cellSize) / 2.0f;
    float yOffset = (cellSize - cellSize) / 2.0f;

    return sf::Vector2f(xPos + xOffset, yPos + yOffset);
}

void initializeGrid(Cell grid[][cols], int rows, int cols, int cellSize, float cellBorderWidth, sf::Color defaultFillColor, sf::Color defaultOutlineColor) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            grid[y][x].position = sf::Vector2i(x, y);
            grid[y][x].impassableTerrain = false;
            grid[y][x].shape = std::make_shared<sf::RectangleShape>(cellShape);
            grid[y][x].shape->setFillColor(defaultFillColor);
            grid[y][x].shape->setOutlineThickness(cellBorderWidth);
            grid[y][x].shape->setOutlineColor(defaultOutlineColor);
            grid[y][x].shape->setPosition(x * cellSize, y * cellSize);
        }
    }
}


int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Cell Grid with Squares", sf::Style::Fullscreen);

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineThickness(cellBorderWidth);
    cell.setOutlineColor(sf::Color(100, 100, 100));

    sf::RectangleShape startSquare(sf::Vector2f(cellSize - cellBorderWidth, cellSize - cellBorderWidth));
    startSquare.setFillColor(sf::Color::Blue);

    sf::RectangleShape endSquare(sf::Vector2f(cellSize - cellBorderWidth, cellSize - cellBorderWidth));
    endSquare.setFillColor(sf::Color::Red);

    Cell grid[rows][cols];
    initializeGrid(grid, rows, cols, cellSize, cellBorderWidth, sf::Color::White, sf::Color(100, 100, 100));

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                cell.setPosition(getScreenPositionFromGridCoordinate(x, y, cellSize));
                window.draw(cell);
            }
        }

        sf::Vector2f startSquarePos = getScreenPositionFromGridCoordinate(startingPos[0], startingPos[1], cellSize);
        startSquare.setPosition(startSquarePos);
        window.draw(startSquare);

        sf::Vector2f endSquarePos = getScreenPositionFromGridCoordinate(endingPos[0], endingPos[1], cellSize);
        endSquare.setPosition(endSquarePos);
        window.draw(endSquare);

        window.display();
    }

    return 0;
}
