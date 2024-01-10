#include "MovementManager.h"

MovementManager::MovementManager(MapInfo** map, const int& newMapSize)
	: mapSize(newMapSize) {
	initialiseMapCells();
}

MovementManager::~MovementManager() {

}

void MovementManager::initialiseMapCells()
{
	mapCells = new Cell**[mapSize];
	for (int i = 0; i < mapSize; i++) {
		mapCells[i] = new Cell*[mapSize];
		for (int j = 0; j < mapSize; j++)
			mapCells[i][j] = nullptr;
	}
}

std::vector<sf::Vector2i> MovementManager::findPath(sf::Vector2i source, sf::Vector2i target)
{
	Cell sourceCell(source, distance(source, target));
	sourceCell.g = 0;

	mapCells[source.x][source.y] = &sourceCell;

	std::vector<Cell*> openSet = { &sourceCell };

	while (!openSet.empty())
	{
		//Currently linearly searches through whole openSet for least g+h value.
		//Possible optimisation is to maintain openSet as a sorted list
		//by binary searching it when adding a new Cell to find its correct position, 
		//then we can simply take openSet[0] here every time.

		int current = 0;
		for (int i = 1; i < openSet.size(); i++)
			if (openSet[current]->g + openSet[current]->h > openSet[i]->g + openSet[i]->h)
				current = i;

		Cell* currentCell = openSet[current];

		if (*currentCell == target)
			return tracePath(*currentCell);

		openSet.erase(std::next(openSet.begin(), current));

		std::vector<sf::Vector2i> neighbours = getNeighboursOf(*currentCell);

		for (sf::Vector2i v : neighbours)
		{
			if (mapCells[v.x][v.y] == nullptr)
				mapCells[v.x][v.y] = new Cell(v, distance(target, v));

			//TEMP: Currently every cell can access its direct neighbours with a cost of 1
			//regardless of obstacles or cliffs/cliff-faces. No diagonal movement at all.

			Cell* neighbour = mapCells[v.x][v.y];
			double temp_g = currentCell->g + 1;

			if (temp_g < neighbour->g)
			{
				neighbour->pred = currentCell;
				neighbour->g = temp_g;

				if (std::find_if(openSet.begin(), openSet.end(), [neigh = neighbour] (Cell* c) { return c == neigh; }) == openSet.end())
					openSet.push_back(neighbour);
			}
		}
	}

	//In case of failure, return an empty path
	return std::vector<sf::Vector2i>();
}

std::vector<sf::Vector2i> MovementManager::getNeighboursOf(Cell& cell)
{
	//TEMP: This will need to be changed when the map is a quadtree, 
	//not a simple cartesian grid

	sf::Vector2i pos = cell.pos;

	//TODO: Consider inpassable terrain/obstacles

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

std::vector<sf::Vector2i> MovementManager::tracePath(Cell& start)
{
	std::vector<sf::Vector2i> path = { start.pos };

	Cell current = start;
	while (current.pred != nullptr) {
		path.insert(path.begin(), current.pred->pos); //Insert at front
		current = *current.pred;
	}

	return path;
}

double MovementManager::distance(sf::Vector2i& v, sf::Vector2i& u)
{
	//Return the square of the Euclidean distance. As long as we only use 
	//the squared values, we can save on computing the sqrt each time as
	//x^2 > y^2 implies that x > y for positive numbers x and y.
	return (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y);

	return std::sqrt(
		(v.x - u.x) * (v.x - u.x) +
		(v.y - u.y) * (v.y - u.y)
	);
}