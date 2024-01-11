#include "MovementManager.h"

MovementManager::MovementManager(const int& newMapSize)
	: mapSize(newMapSize) {
	initialiseMapNodes();
}

MovementManager::~MovementManager() {

}

void MovementManager::initialiseMapNodes()
{
	mapNodes = new Node**[mapSize];
	for (int i = 0; i < mapSize; i++) {
		mapNodes[i] = new Node*[mapSize];
		for (int j = 0; j < mapSize; j++)
			mapNodes[i][j] = nullptr;
	}
}

std::vector<sf::Vector2i> MovementManager::AStarPathFind(sf::Vector2i source, sf::Vector2i target)
{
	Node sourceNode(source, euclideanDistance(source, target));
	sourceNode.g = 0;

	mapNodes[source.x][source.y] = &sourceNode;

	std::vector<Node*> openSet = { &sourceNode };

	while (!openSet.empty())
	{
		int current = 0;
		for (int i = 1; i < openSet.size(); i++)
			if (openSet[current]->g + openSet[current]->h > openSet[i]->g + openSet[i]->h)
				current = i;

		Node* currentNode = openSet[current];

		if (*currentNode == target)
			return retracePath(*currentNode);

		openSet.erase(std::next(openSet.begin(), current));

		std::vector<sf::Vector2i> neighbours = getNeighboursOf(*currentNode);

		for (sf::Vector2i v : neighbours)
		{
			if (mapNodes[v.x][v.y] == nullptr)
				mapNodes[v.x][v.y] = new Node(v, euclideanDistance(target, v));

			Node* neighbour = mapNodes[v.x][v.y];
			double temp_g = currentNode->g + 1;

			if (temp_g < neighbour->g)
			{
				neighbour->pred = currentNode;
				neighbour->g = temp_g;

				if (std::find_if(openSet.begin(), openSet.end(), [neigh = neighbour] (Node* c) { return c == neigh; }) == openSet.end())
					openSet.push_back(neighbour);
			}
		}
	}

	return std::vector<sf::Vector2i>();
}

std::vector<sf::Vector2i> MovementManager::getNeighboursOf(Node& node) const
{
	sf::Vector2i pos = node.pos;

	std::vector<sf::Vector2i> neighbours = std::vector<sf::Vector2i>();

	if (pos.x != 0)
		neighbours.push_back(sf::Vector2i(pos.x - 1, pos.y));
	if (pos.x != mapSize - 1)
		neighbours.push_back(sf::Vector2i(pos.x + 1, pos.y));
	if (pos.y != 0)
		neighbours.push_back(sf::Vector2i(pos.x, pos.y - 1));
	if (pos.y != mapSize - 1)
		neighbours.push_back(sf::Vector2i(pos.x, pos.y + 1));

	return neighbours;
}

std::vector<sf::Vector2i> MovementManager::retracePath(Node& start)
{
	std::vector<sf::Vector2i> path = { start.pos };

	Node current = start;
	while (current.pred != nullptr) {
		path.insert(path.begin(), current.pred->pos);
		current = *current.pred;
	}

	return path;
}

double MovementManager::euclideanDistance(sf::Vector2i& v, sf::Vector2i& u) const
{
	return (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y);
}