#include <SFML/Graphics.hpp>
#include <iostream>

const int rows = 10;
const int cols = 10;
const int border = 10;
const int cellSize = 80;
const int cellBorderWidth = 4;

const std::vector<int> startingPos = { 0, 0 };
const std::vector<int> endingPos = { 9,9 };

struct Cell {
    sf::Vector2i position;
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

double calculateEuclideanDistance(const Node& node, const Node& goal) {
    return std::sqrt(std::pow(node.x - goal.x, 2) + std::pow(node.y - goal.y, 2));
}

std::vector<Node> openList;
std::vector<Node> closedList;
std::vector<Node> pathList;


void AStarPathfinding(const Node& start, const Node& goal) {


    openList.push_back(start);

    while (!openList.empty()) {
        // Find the node in the open list with the lowest fScore
        auto current = openList.begin();
        for (auto it = openList.begin() + 1; it != openList.end(); ++it) {
            if ((*it).fScore < (*current).fScore) {
                current = it;
            }
        }

        // Move the current node from the open list to the closed list
        closedList.push_back(*current);
        openList.erase(current);

        // Check if we've reached the goal
        if (closedList.back().x == goal.x && closedList.back().y == goal.y) {
            std::cout << "Goal reached!" << std::endl;
            break;
        }

        // Generate neighbors of the current node
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                // Skip the current node
                if (dx == 0 && dy == 0) continue;

                int neighborX = closedList.back().x + dx;
                int neighborY = closedList.back().y + dy;

                // Check if the neighbor is within the grid boundaries
                if (neighborX >= 0 && neighborX < cols && neighborY >= 0 && neighborY < rows) {
                    // Create a new neighbor node
                    Node neighbor(neighborX, neighborY);
                    neighbor.gScore = closedList.back().gScore + 1; // Assuming each step has a cost of 1
                    neighbor.hScore = calculateEuclideanDistance(neighbor, goal);
                    neighbor.fScore = neighbor.gScore + neighbor.hScore;
                    neighbor.parent = &closedList.back();

                    // Check if the neighbor is already in the closed list
                    bool inClosedList = false;
                    for (const auto& node : closedList) {
                        if (node.x == neighbor.x && node.y == neighbor.y) {
                            inClosedList = true;
                            break;
                        }
                    }

                    if (!inClosedList) {
                        // Check if the neighbor is already in the open list
                        auto openIt = std::find_if(openList.begin(), openList.end(), [&neighbor](const Node& node) {
                            return node.x == neighbor.x && node.y == neighbor.y;
                            });

                        // If the neighbor is not in the open list or has a better path
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

    float xPos = x * cellSize + border;
    float yPos = y * cellSize + border;

    float xOffset = (cellSize - cellSize) / 2.0f;
    float yOffset = (cellSize - cellSize) / 2.0f;

    return sf::Vector2f(xPos + xOffset, yPos + yOffset);
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

    Node startNode(startingPos[0], startingPos[1]);
    Node goalNode(endingPos[0], endingPos[1]);

    AStarPathfinding(startNode, goalNode);

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
        
        for (const auto& node : closedList) {
            sf::Vector2f squarePos = getScreenPositionFromGridCoordinate(node.x, node.y, cellSize);
            cell.setPosition(squarePos);

            if (node.isInPath) {
                cell.setFillColor(sf::Color(255, 255, 200)); 
            }
            else {
                cell.setFillColor(sf::Color(100, 208, 0));
            }

            window.draw(cell);
        }
        
        sf::Vector2f startSquarePos = getScreenPositionFromGridCoordinate(startingPos[0], startingPos[1], cellSize);
        startSquare.setPosition(startSquarePos);
        window.draw(startSquare);

        sf::Vector2f endSquarePos = getScreenPositionFromGridCoordinate(endingPos[0], endingPos[1], cellSize);
        endSquare.setPosition(endSquarePos);
        window.draw(endSquare);

        window.display();
    }
    std::cout << "Closed List: ";
    for (const auto& node : closedList) {
        std::cout << "(" << node.x << ", " << node.y << ") ";
    }
    std::cout << std::endl;

    return 0;
}
