#include <SFML/Graphics.hpp>
#include <queue>
#include <set>
#include <unordered_set>
#include <iostream>
#include <memory>
#include <cmath>

const int rows = 25;
const int cols = 25;
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


const std::vector<int> endingPos = { 12, 12 };
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
  wall18
};

struct Cell {
    sf::Vector2f screenPosition;
    sf::Vector2i position;
    bool impassableTerrain;
    std::shared_ptr<sf::RectangleShape> shape;
    int direction;
    int distance;
    int rotation;
    int cost;
};

void GenerateDistanceMap(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    int goalX = endingPos[0];
    int goalY = endingPos[1];

    std::queue<std::pair<int, int>> queue;

    queue.push({ goalY, goalX });
    grid[goalY][goalX].distance = 0;

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    const std::vector<std::pair<int, int>> direction = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    while (!queue.empty()) {
        int y = queue.front().first;
        int x = queue.front().second;
        queue.pop();

        visited[y][x] = true;

        for (int i = 0; i < 7; ++i) {
            int newY = y + direction[i].first;
            int newX = x + direction[i].second;

            if (newY >= 0 && newY < rows && newX >= 0 && newX < cols && !visited[newY][newX] && grid[newY][newX].distance != 255) {

                int neighborDistance = (i < 4) ? 10 : 14; 

                int tentativeDistance = grid[y][x].distance + neighborDistance + grid[newY][newX].cost;

                if (tentativeDistance < grid[newY][newX].distance || grid[newY][newX].distance == 0) {
                    grid[newY][newX].distance = tentativeDistance;
                    queue.push({ newY, newX });
                }
            }
        }
    }
}

void PropegateWaveFront(Cell(&grid)[rows][cols], const std::vector<int>& endingPos) {
    std::unordered_set<Cell> WaveFrontCellsList;
    std::vector<Cell> NewNeighbourList;

    // Initialize WaveFrontCellsList with the target cell
    Cell targetCell = grid[endingPos[0]][endingPos[1]];
    targetCell.distance = 1;  // Set distance of target cell to 1
    WaveFrontCellsList.insert(targetCell);

    while (!WaveFrontCellsList.empty()) {
        // Step 1: Expand
        for (std::unordered_set<Cell>::iterator it = WaveFrontCellsList.begin(); it != WaveFrontCellsList.end(); ) {
            const Cell& cell = *it;
            // Update Distance value
            // Explore neighbors of the current WaveFrontCellsList cell
            // If a neighbor cell's distance value is 0, add it to the NewNeighbourList
            // Calculate the distance-from-target value for new neighbor cells by taking current cell.distance and add 1
            // Break condition: if the source cell is reached, else all grid is visited

            // Step 2: Update
            for (const Cell& newNeighbour : NewNeighbourList) {
                // Move all cells from NewNeighbourList to WaveFrontCellList
                // If the cell is not already in WaveFrontCellsList, add it
                // If the cell is already in WaveFrontCellsList, update its distance value if the new value is smaller
            }

            // After processing, remove the cell from WaveFrontCellsList
            it = WaveFrontCellsList.erase(it);
        }
        NewNeighbourList.clear();
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
            grid[y][x].screenPosition = getScreenPositionFromGridCoordinate(x, y, cellSize);
            grid[y][x].impassableTerrain = false;
            grid[y][x].shape = std::make_shared<sf::RectangleShape>(cellShape);
            grid[y][x].shape->setFillColor(defaultFillColor);
            grid[y][x].shape->setOutlineThickness(cellBorderWidth);
            grid[y][x].shape->setOutlineColor(defaultOutlineColor);
            grid[y][x].shape->setPosition(x * cellSize, y * cellSize);
            grid[y][x].direction = 0;
            grid[y][x].distance = 0; 
            grid[y][x].rotation = 0;
            grid[y][x].cost = 1;
        }
    }
}

void initialiseWalls(Cell grid[][cols], const std::vector<std::vector<int>>& wallSections) {
    for (const std::vector<int>& wall : wallSections) {
        int wallX = wall[1]; 
        int wallY = wall[0]; 

        if (wallX >= 0 && wallX < cols && wallY >= 0 && wallY < rows) {
            grid[wallY][wallX].distance = -1;
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

    Cell grid[rows][cols];
    initializeGrid(grid, rows, cols, cellSize, cellBorderWidth, sf::Color::White, sf::Color(100, 100, 100));
    initialiseWalls(grid, wallSections);
    VectorFieldPathfinding(endingPos, grid);

    
    sf::VertexArray gridVertices(sf::Quads, rows * cols * 4); 

    int vertexIndex = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Cell currentCell = grid[y][x];
            sf::Vector2f position = currentCell.screenPosition;

            gridVertices[vertexIndex + 0].position = position;
            gridVertices[vertexIndex + 1].position = position + sf::Vector2f(cellSize, 0);
            gridVertices[vertexIndex + 2].position = position + sf::Vector2f(cellSize, cellSize);
            gridVertices[vertexIndex + 3].position = position + sf::Vector2f(0, cellSize);

            gridVertices[vertexIndex + 0].color = sf::Color::White;
            gridVertices[vertexIndex + 1].color = sf::Color::White;
            gridVertices[vertexIndex + 2].color = sf::Color::White;
            gridVertices[vertexIndex + 3].color = sf::Color::White;

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
                Cell currentCell = grid[y][x];
                cell.setPosition(currentCell.screenPosition);
                window.draw(cell);
                drawArrowOnCell(window, currentCell);

                if (grid[y][x].cost == 255) {
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

    //PrintCosts(grid, endingPos);
    PrintDistances(grid, endingPos);
    //PrintRotations(grid, endingPos);

    return 0;
}
