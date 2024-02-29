#include <SFML/Graphics.hpp>
#include <iostream>

const int rows = 10;
const int cols = 10;
const int border = 10;
const int cellSize = 80;
const int cellBorderWidth = 4;
const sf::Vector2f cellShape(static_cast<float>(cellSize), static_cast<float>(cellSize)); 

const bool impassable = true;

const std::vector<int> startingPos = { 0, 0 };
const std::vector<int> endingPos = {9 , 2 };

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

int calculateHeuristicDistance(const Node& node, const Node& goal) {
    int dx = abs(node.x - goal.x);
    int dy = abs(node.y - goal.y);

    bool isDiagonal = (dx > 0) && (dy > 0);

    return (isDiagonal ? 14 : 10) * std::max(dx, dy);
}


std::vector<Node> openList;
std::vector<Node> closedList;
std::vector<Node> pathList;

void AStarPathfinding(const Node& start, const Node& goal, const Cell grid[][cols]) {
    // Clear lists and add starting node to open list
    openList.clear();
    closedList.clear();
    pathList.clear();
    openList.push_back(start);

    while (!openList.empty()) {
        // Find node with the lowest fScore in open list
        auto current = openList.begin();
        for (auto it = openList.begin() + 1; it != openList.end(); ++it) {
            if ((*it).fScore < (*current).fScore) {
                current = it;
            }
        }

        // Move current node to closed list and remove from open list
        closedList.push_back(*current);
        openList.erase(current);

        // Check if goal is reached
        if (closedList.back().x == goal.x && closedList.back().y == goal.y) {
            std::cout << "Goal reached!" << std::endl;
            break;
        }

        // Iterate through neighbors in a 3x3 grid (excluding center)
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {

                if (dx == 0 && dy == 0) continue;

                int neighborX = closedList.back().x + dx;
                int neighborY = closedList.back().y + dy;

                // **Changes:** Check if neighbor is within bounds and not impassable
                if (neighborX >= 0 && neighborX < cols && neighborY >= 0 && neighborY < rows &&
                    !grid[neighborY][neighborX].impassableTerrain) {

                    // Create neighbor node, calculate scores, and set parent
                    Node neighbor(neighborX, neighborY);
                    neighbor.gScore = closedList.back().gScore + 1;
                    neighbor.hScore = calculateHeuristicDistance(neighbor, goal);
                    neighbor.fScore = neighbor.gScore + neighbor.hScore;
                    neighbor.parent = new Node(closedList.back().x, closedList.back().y);

                    // Check if neighbor is in closed list or open list with higher gScore
                    bool inClosedList = false;
                    for (const auto& node : closedList) {
                        if (node.x == neighbor.x && node.y == neighbor.y) {
                            inClosedList = true;
                            break;
                        }
                    }
                    if (!inClosedList) {
                        auto openIt = std::find_if(openList.begin(), openList.end(), [&neighbor](const Node& node) {
                            return node.x == neighbor.x && node.y == neighbor.y;
                            });
                        if (openIt == openList.end() || neighbor.gScore < openIt->gScore) {
                            if (openIt != openList.end()) {
                                openList.erase(openIt);
                            }
                            openList.push_back(neighbor);
                        }
                    }
                }
            }
        }
    }
}


sf::Vector2f getScreenPositionFromGridCoordinate(int x, int y, int cellSize) {
    if (x < 0 || x >= cols || y < 0 || y >= rows) {
        return sf::Vector2f(-1.0f, -1.0f);
    }

    float xPos = x * cellSize;
    float yPos = y * cellSize;

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


    sf::RectangleShape startSquare(sf::Vector2f(cellSize - cellBorderWidth, cellSize - cellBorderWidth));
    startSquare.setFillColor(sf::Color::Blue);

    sf::RectangleShape endSquare(sf::Vector2f(cellSize - cellBorderWidth, cellSize - cellBorderWidth));
    endSquare.setFillColor(sf::Color::Red);

    Node startNode(startingPos[0], startingPos[1]);
    Node goalNode(endingPos[0], endingPos[1]);

    Cell grid[rows][cols];
    initializeGrid(grid, rows, cols, cellSize, cellBorderWidth, sf::Color::White, sf::Color(100, 100, 100));
    grid[1][1].impassableTerrain = impassable;
    grid[1][2].impassableTerrain = impassable;
    grid[1][3].impassableTerrain = impassable;
    grid[1][4].impassableTerrain = impassable;
    grid[1][5].impassableTerrain = impassable;
    grid[1][6].impassableTerrain = impassable;
    grid[1][7].impassableTerrain = impassable;
    grid[1][8].impassableTerrain = impassable;
    grid[1][9].impassableTerrain = impassable;

    AStarPathfinding(startNode, goalNode, grid);

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
                if (grid[y][x].shape) {

                    sf::Color cellColor;

                    if (grid[y][x].impassableTerrain) {
                        cellColor = sf::Color::Black; 
                    }
                    else if (!closedList.empty()) { 
                        bool isPathNode = false;
                        for (const auto& pathNode : closedList) {
                            if (pathNode.x == x && pathNode.y == y) {
                                isPathNode = true;
                                cellColor = sf::Color(100, 208, 0);
                                break;
                            }
                        }
                        if (!isPathNode) {
                            cellColor = sf::Color::White;
                        }
                    }
                    else {
                        cellColor = sf::Color::White;
                    }

                    grid[y][x].shape->setFillColor(cellColor);

                    window.draw(*grid[y][x].shape);
                }
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
