#include <SFML/Graphics.hpp>
#include <iostream>

const int rows = 10;
const int cols = 10;
const int border = 10;
const int cellSize = 80;
const int cellBorderWidth = 4;

const std::vector<int> startingPos = { 0, 0 };
const std::vector<int> endingPos = { 6, 9 };

struct Cell {
    sf::Vector2i position;
    bool impassableTerrain;
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


void AStarPathfinding(const Node& start, const Node& goal) {
    openList.clear();
    closedList.clear();
    pathList.clear();

    openList.push_back(start);

    while (!openList.empty()) {
        auto current = openList.begin();
        for (auto it = openList.begin() + 1; it != openList.end(); ++it) {
            if ((*it).fScore < (*current).fScore) {
                current = it;
            }
        }

        closedList.push_back(*current);
        openList.erase(current);

        if (closedList.back().x == goal.x && closedList.back().y == goal.y) {
            std::cout << "Goal reached!" << std::endl;
            break;
        }

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {

                if (dx == 0 && dy == 0) continue;

                int neighborX = closedList.back().x + dx;
                int neighborY = closedList.back().y + dy;


                if (neighborX >= 0 && neighborX < cols && neighborY >= 0 && neighborY < rows) {
                    Node neighbor(neighborX, neighborY);
                    neighbor.gScore = closedList.back().gScore + 1;
                    neighbor.hScore = calculateHeuristicDistance(neighbor, goal);
                    neighbor.fScore = neighbor.gScore + neighbor.hScore;
                    neighbor.parent = new Node(closedList.back().x, closedList.back().y);

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
                sf::Vector2f squarePos = getScreenPositionFromGridCoordinate(x, y, cellSize);
                cell.setPosition(squarePos);

                bool isPathNode = false;
                for (const auto& pathNode : closedList) {
                    if (pathNode.x == x && pathNode.y == y) {
                        cell.setFillColor(sf::Color(100, 208, 0));
                        isPathNode = true;
                        break;
                    }
                }

                if (!isPathNode) {
                    cell.setFillColor(sf::Color::White);
                }
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
