#include <SFML/Graphics.hpp>
#include <queue>
#include <set>
#include <iostream>
#include <memory>
#include <cmath>


const int rows = 10;
const int cols = 10;
const int border = 10;
const int cellSize = 80;
const int cellBorderWidth = 4;
const sf::Vector2f cellShape(static_cast<float>(cellSize), static_cast<float>(cellSize));
sf::Sprite arrowSprite;
sf::Texture arrowTexture;


void initializeArrowSprite() {
    const std::string arrowImagePath = "../resources/images/Utilities/vectorFieldPointer.png";

    if (!arrowTexture.loadFromFile(arrowImagePath)) {
        std::cerr << "Error loading arrow texture: " << arrowImagePath << std::endl;
        return;
    }

    if (arrowTexture.getSize().x == 0 || arrowTexture.getSize().y == 0) {
        std::cerr << "Error: Loaded texture has zero size." << std::endl;
        return;
    }

    arrowSprite.setTexture(arrowTexture);

}

const std::vector<int> startingPos = { 6, 6 };
const std::vector<int> endingPos = { 7, 7 };

struct Cell {
    sf::Vector2i position;
    bool impassableTerrain;
    std::shared_ptr<sf::RectangleShape> shape;
    sf::Vector2f direction;
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

void VectorFieldPathfinding(const std::vector<int>& endingPos, Cell(&grid)[rows][cols]) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (x % 2 == 0) {
                grid[y][x].direction = sf::Vector2f(-1.0f, 0.0f);
            }
            else {
                grid[y][x].direction = sf::Vector2f(1.0f, 0.0f);
            }
        }
    }
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

void drawArrowOnCell(sf::RenderWindow& window, const Cell& cell) {
    sf::Vector2f spriteSize(50.0f, 50.0f);
    sf::Vector2f cellCenter = cell.shape->getPosition() +
        sf::Vector2f(border + (cellSize - 2 * cellBorderWidth) / 2.0f,
            border + (cellSize - 2 * cellBorderWidth) / 2.0f);

    float arrowScale = std::min(cell.shape->getSize().x / spriteSize.x,
        cell.shape->getSize().y / spriteSize.y);

    arrowSprite.setOrigin(spriteSize / 2.0f);
    arrowSprite.setPosition(cellCenter);
    arrowSprite.setScale(arrowScale, arrowScale);

    float angleInRadians = std::atan2(cell.direction.y, cell.direction.x);
    float rotationDegrees = angleInRadians * 180.0f / 3.14159f;

    arrowSprite.setRotation(rotationDegrees);
    window.draw(arrowSprite);
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
            grid[y][x].direction = sf::Vector2f(0.0f, 0.0f);
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

    initializeArrowSprite();

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
        VectorFieldPathfinding(endingPos, grid);

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                Cell currentCell = grid[y][x];
                cell.setPosition(getScreenPositionFromGridCoordinate(x, y, cellSize));
                window.draw(cell);
                drawArrowOnCell(window, currentCell);
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
