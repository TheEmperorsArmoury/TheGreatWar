#include <SFML/Graphics.hpp>
#include <queue>
#include <iostream>
#include <memory>
#include <cmath>
#include <list>
#include <tuple>
#include <algorithm> 
#include <unordered_set>


const int rows = 25;
const int cols = 26;
const int border = 10;
const int cellSize = 40;
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


const std::vector<int> startingPos = { 0,0 };
const std::vector<int> wall1 = { 9, 10 };
const std::vector<int> wall2 = { 10, 10 };
const std::vector<int> wall3 = { 11, 10 };
const std::vector<int> wall4 = { 12, 10 };
const std::vector<int> wall5 = { 13, 10 };
const std::vector<int> wall6 = { 9, 9 };
const std::vector<int> wall7 = { 9, 10 };
const std::vector<int> wall8 = { 9, 11 };
const std::vector<int> wall9 = { 9, 12 };
const std::vector<int> wall10 = { 9, 13 };
const std::vector<int> wall11 = { 9, 14 };
const std::vector<int> wall12 = { 9, 15};
const std::vector<int> wall13 = { 10, 15};
const std::vector<int> wall14 = { 11,15};
const std::vector<int> wall15 = { 12, 15};
const std::vector<int> wall16 = { 13, 15};
const std::vector<int> wall17 = { 14, 15};
const std::vector<int> wall18 = {15, 15};

const std::vector<int> wall19 = { 14, 10 };
const std::vector<int> wall20 = { 15, 10 };
const std::vector<int> wall21 = { 15, 11 };
const std::vector<int> wall22 = { 15, 12 };
const std::vector<int> endingPos = { 24,24 };


std::vector<std::vector<int>> wallSections = {
  wall1, 
  wall2, 
  wall3, 
  wall4, 
  wall5,
  wall6,
  wall7,
  wall8,
  wall9,
  wall10,
  wall11,
  wall12,
  wall13,
  wall14,
  wall15,
  wall16,
  wall17,
  wall18,
  wall19,
  wall20,
  wall21,
  wall22
};

struct Cell {
    sf::Vector2f screenPosition;
    sf::Vector2i position;
    bool impassableTerrain;
    std::shared_ptr<sf::RectangleShape> shape;
    int distance;
    int rotation;
    int cost;
    int positionHash;
};

Cell grid[rows][cols];
Cell ghostGrid[rows][cols];
std::unordered_set<int> pathCells = { 0, 27, 54, 81, 108, 135, 162, 189, 216, 243, 270, 297, 324, 351, 378, 405, 432, 459, 486, 513, 540, 567, 594, 621, 648 };


void PropagateWaveFront() {
    std::list<std::tuple<int, int, int>> nodes;
    nodes.push_back({ endingPos[0], endingPos[1], 1 });

    while (!nodes.empty()) {
        std::list<std::tuple<int, int, int>> new_nodes;

        for (auto& n : nodes) {
            int x = std::get<0>(n);
            int y = std::get<1>(n);
            int d = std::get<2>(n);

            grid[y][x].distance = d;

            if ((x + 1) < cols && grid[y][x + 1].distance == 0)
                new_nodes.push_back({ x + 1, y, d + 1 });

            if ((x - 1) >= 0 && grid[y][x - 1].distance == 0)
                new_nodes.push_back({ x - 1, y, d + 1 });

            if ((y + 1) < rows && grid[y + 1][x].distance == 0)
                new_nodes.push_back({ x, y + 1, d + 1 });

            if ((y - 1) >= 0 && grid[y - 1][x].distance == 0)
                new_nodes.push_back({ x, y - 1, d + 1 });
        }

        new_nodes.sort([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2) {
            if (std::get<0>(n1) != std::get<0>(n2))
                return std::get<0>(n1) < std::get<0>(n2);
            return std::get<1>(n1) < std::get<1>(n2);
            });

        new_nodes.unique([&](const std::tuple<int, int, int>& n1, const std::tuple<int, int, int>& n2) {
            return std::get<0>(n1) == std::get<0>(n2) && std::get<1>(n1) == std::get<1>(n2);
            });

        nodes.clear();
        nodes.insert(nodes.begin(), new_nodes.begin(), new_nodes.end());
    }
}

void CalculateCellRotations(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    int goalX = endingPos[0];
    int goalY = endingPos[1];

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::vector<std::pair<int, int>> neighbors = { {315, 0}, {0, 0}, {45, 0}, {270, 0}, {90, 0}, {225, 0}, {180, 0}, {135, 0} };
            int counter = 0;
            for (int neighborY = y - 1; neighborY <= y + 1; ++neighborY) {
                for (int neighborX = x - 1; neighborX <= x + 1; ++neighborX) {
                    if (!(neighborX == x && neighborY == y)) { 
                        int distanceValue;
                        if (neighborX >= 0 && neighborX < cols && neighborY >= 0 && neighborY < rows) {
                            distanceValue = grid[neighborY][neighborX].distance;
                        }
                        else {
                            distanceValue = grid[y][x].distance + 255;
                        }
                        neighbors[counter].second = distanceValue;
                        ++counter;
                    }
                }
            }
            std::sort(neighbors.begin(), neighbors.end(), [](const auto& a, const auto& b) {
                return a.second < b.second;
                });

            grid[y][x].rotation = neighbors[0].first;
        }
    }
}

void VectorFieldPathfinding(const std::vector<int>& endingPos, Cell(&grid)[rows][cols]) {
    PropagateWaveFront();
    CalculateCellRotations(ghostGrid, endingPos);
    
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

int hash(int x, int y, int cols) {
    return y * cols + x;
}

void initializeGhostGrid(Cell ghostGrid[][cols], int rows, int cols, int cellSize, float cellBorderWidth, sf::Color defaultFillColor, sf::Color defaultOutlineColor) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int positionHash = hash(x, y, cols);

            ghostGrid[y][x].position = sf::Vector2i(x, y);
            ghostGrid[y][x].cost = 1;
            ghostGrid[y][x].screenPosition = getScreenPositionFromGridCoordinate(x, y, cellSize);
            ghostGrid[y][x].impassableTerrain = false;
            ghostGrid[y][x].shape = std::make_shared<sf::RectangleShape>(cellShape);
            ghostGrid[y][x].shape->setOutlineThickness(cellBorderWidth);
            ghostGrid[y][x].shape->setOutlineColor(defaultOutlineColor);
            ghostGrid[y][x].shape->setPosition(x * cellSize, y * cellSize);
            ghostGrid[y][x].distance = 0;
            ghostGrid[y][x].rotation = 0;

            if (pathCells.count(positionHash) > 0) {
                ghostGrid[y][x].positionHash = positionHash;
            }
            else {
                ghostGrid[y][x].positionHash = -1;
            }
        }
    }
}

void initialiseWalls(Cell grid[][cols], const std::vector<std::vector<int>>& wallSections) {
    for (const std::vector<int>& wall : wallSections) {
        int wallX = wall[1]; 
        int wallY = wall[0]; 

        if (wallX >= 0 && wallX < cols && wallY >= 0 && wallY < rows) {
            grid[wallY][wallX].distance = 255;
            grid[wallY][wallX].cost = 255; 
        }
    }
}

void PrintCosts(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    VectorFieldPathfinding(endingPos, grid);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::cout << grid[y][x].cost << " ";
        }
        std::cout << std::endl;
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

void PrintGhostHashes(Cell(&ghostGrid)[rows][cols], const std::vector<int>& endingPos) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::cout << ghostGrid[y][x].positionHash << " ";
        }
        std::cout << std::endl;
    }
}

void PrintSomething()
{
    std::cout << "Something" << std::endl;
}

int main() {

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Cell Grid with Squares", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

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

    initializeGhostGrid(ghostGrid, rows, cols, cellSize, cellBorderWidth, sf::Color::White, sf::Color(100, 100, 100));
    //initializeGrid(grid, rows, cols, cellSize, cellBorderWidth, sf::Color::White, sf::Color(100, 100, 100));
    //initialiseWalls(grid, wallSections);
    VectorFieldPathfinding(endingPos, ghostGrid);



    
    sf::VertexArray gridVertices(sf::Quads, rows * cols * 4); 

    int vertexIndex = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Cell currentCell = ghostGrid[y][x];
            sf::Vector2f position = currentCell.screenPosition;

            sf::Color cellColor;

            if (pathCells.count(currentCell.positionHash) > 0) {
                cellColor = sf::Color(255, 255, 255);
            }
            else {
                cellColor = sf::Color(150, 150, 150);
            }

            // Set positions (unchanged)
            gridVertices[vertexIndex + 0].position = position;
            gridVertices[vertexIndex + 1].position = position + sf::Vector2f(cellSize, 0);
            gridVertices[vertexIndex + 2].position = position + sf::Vector2f(cellSize, cellSize);
            gridVertices[vertexIndex + 3].position = position + sf::Vector2f(0, cellSize);

            // Set colors based on pathCells
            gridVertices[vertexIndex + 0].color = cellColor;
            gridVertices[vertexIndex + 1].color = cellColor;
            gridVertices[vertexIndex + 2].color = cellColor;
            gridVertices[vertexIndex + 3].color = cellColor;

            vertexIndex += 4;
        }
    }
    
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
        
        window.draw(gridVertices);
       
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                Cell currentCell = ghostGrid[y][x];
                int positionHash = currentCell.positionHash;

                if (pathCells.count(positionHash) > 0) {
                    cell.setPosition(currentCell.screenPosition);
                    window.draw(cell);

                    drawArrowOnCell(window, currentCell);
                }

                if (currentCell.cost == 255) {
                    wallSquare.setPosition(getScreenPositionFromGridCoordinate(x, y, cellSize));
                    window.draw(wallSquare);
                }
            }
        }
       
        sf::Vector2f endSquarePosition = getScreenPositionFromGridCoordinate(endingPos[0], endingPos[1], cellSize);
        endSquare.setPosition(endSquarePosition);
        window.draw(endSquare);
          
        

        window.display();
    }
    
    //PrintCosts(ghostGrid, endingPos);
    PrintDistances(grid, endingPos);
    //PrintRotations(grid, endingPos);
    //PrintGhostHashes(ghostGrid, endingPos);

    return 0;
}
