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
    arrowSprite.setRotation(0.0f);
}


const std::vector<int> endingPos = { 9,9 };
const std::vector<int> wall1 = { 3,4 };
const std::vector<int> wall2 = { 3,5 };
const std::vector<int> wall3 = { 3,6 };
const std::vector<int> wall4 = { 3,7 };

std::vector<std::vector<int>> wallSections = {
  wall1, 
  wall2, 
  wall3, 
  wall4 
};

struct Cell {
    sf::Vector2i position;
    bool impassableTerrain;
    std::shared_ptr<sf::RectangleShape> shape;
    int direction;
    int distance;
    int rotation;
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

void GenerateDistanceMap(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    int goalX = endingPos[0];
    int goalY = endingPos[1];

    std::queue<std::pair<int, int>> queue;

    queue.push({ goalY, goalX });
    grid[goalY][goalX].distance = 0;

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    const std::vector<std::pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    while (!queue.empty()) {
        int y = queue.front().first;
        int x = queue.front().second;
        queue.pop();

        visited[y][x] = true;

        for (auto& direction : directions) {
            int newY = y + direction.first;
            int newX = x + direction.second;

            if (newY >= 0 && newY < rows && newX >= 0 && newX < cols && !visited[newY][newX] && grid[newY][newX].distance != 1000) {
                int distanceToGoal = static_cast<int>(10 * std::sqrt(std::pow(goalX - newX, 2) + std::pow(goalY - newY, 2)));

                int neighborDistance = direction.first == 0 || direction.second == 0 ? 10 : 14;

                if (distanceToGoal + grid[y][x].distance < grid[newY][newX].distance || grid[newY][newX].distance == 0) {
                    grid[newY][newX].distance = distanceToGoal + grid[y][x].distance;
                    queue.push({ newY, newX });
                }
            }
        }
    }
}

void CalculateCellRotations(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    int goalX = endingPos[0];
    int goalY = endingPos[1];
    std::queue<std::pair<int, int>> queue;

    const std::vector<std::pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    queue.push({ goalY, goalX });

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    while (!queue.empty()) {
        int y = queue.front().first;
        int x = queue.front().second;
        queue.pop();

        visited[y][x] = true;

        int minDistance = INT_MAX;
        int bestNeighborX = 0;
        int bestNeighborY = 0;

        for (int neighborY = y - 1; neighborY <= y + 1; ++neighborY) {
            for (int neighborX = x - 1; neighborX <= x + 1; ++neighborX) {
                if (neighborX < 0 || neighborX >= cols || neighborY < 0 || neighborY >= rows || (neighborX == x && neighborY == y)) {
                    continue;
                }

                if (grid[neighborY][neighborX].distance < minDistance) {
                    minDistance = grid[neighborY][neighborX].distance;
                    bestNeighborX = neighborX;
                    bestNeighborY = neighborY;
                }
            }
        }
        float dx = bestNeighborX - x;
        float dy = bestNeighborY - y;
        float angle = std::atan2(dy, dx); 
        angle = angle * 180.0f / 3.14; 
        angle = std::fmod(angle + 360.0f, 360.0f); 

        grid[y][x].rotation = angle + 90;

        for (auto& direction : directions) {
            int newY = y + direction.first;
            int newX = x + direction.second;

            if (newY >= 0 && newY < rows && newX >= 0 && newX < cols && !visited[newY][newX]) {
                queue.push({ newY, newX });
            }
        }
    }
}



void VectorFieldPathfinding(const std::vector<int>& endingPos, Cell(&grid)[rows][cols]) {

    GenerateDistanceMap(grid, endingPos);
    CalculateCellRotations(grid, endingPos);
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

    float rotationDegrees = static_cast<float>(cell.rotation);

    arrowSprite.setRotation(rotationDegrees);
    window.draw(arrowSprite);
}




void initializeGrid(Cell grid[][cols], int rows, int cols, int cellSize, float cellBorderWidth, sf::Color defaultFillColor, sf::Color defaultOutlineColor) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            grid[y][x].position = sf::Vector2i(x, y);
            grid[y][x].impassableTerrain = false;
            grid[y][x].distance = (y == 2 && (x >= 2 && x <= 5)) ? 1000 : 0;
            grid[y][x].shape = std::make_shared<sf::RectangleShape>(cellShape);
            grid[y][x].shape->setFillColor(defaultFillColor);
            grid[y][x].shape->setOutlineThickness(cellBorderWidth);
            grid[y][x].shape->setOutlineColor(defaultOutlineColor);
            grid[y][x].shape->setPosition(x * cellSize, y * cellSize);
            grid[y][x].direction = 0;
        }
    }
}



void PrintDistances(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    VectorFieldPathfinding(endingPos, grid);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::cout << grid[y][x].distance << " ";
        }
        std::cout << std::endl;
    }
}

void PrintRotations(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    VectorFieldPathfinding(endingPos, grid);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::cout << grid[y][x].rotation << " ";
        }
        std::cout << std::endl;
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

    sf::RectangleShape wallSquare(sf::Vector2f(cellSize - cellBorderWidth, cellSize - cellBorderWidth));
    wallSquare.setFillColor(sf::Color::Black);



    initializeArrowSprite();

    Cell grid[rows][cols];
    initializeGrid(grid, rows, cols, cellSize, cellBorderWidth, sf::Color::White, sf::Color(100, 100, 100));
    VectorFieldPathfinding(endingPos, grid);


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

                // Draw black square if distance is 1000
                if (grid[y][x].distance == 1000) {
                    wallSquare.setPosition(getScreenPositionFromGridCoordinate(x, y, cellSize));
                    window.draw(wallSquare);
                }
            }
        }
       
        sf::Vector2f endSquarePos = getScreenPositionFromGridCoordinate(endingPos[0], endingPos[1], cellSize);
        endSquare.setPosition(endSquarePos);
        window.draw(endSquare);

        window.display();
    }   
    PrintDistances(grid, endingPos);
    //PrintRotations(grid, endingPos);

    return 0;
}
