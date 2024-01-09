#include "Agent.h"

Agent::Agent(sf::Vector2i newPos)
	: pos(newPos) {
}

Agent::~Agent()
{
}

sf::Vector2i* Agent::findPath(sf::Vector2i dest, const int& mapSize) 
{
	Cell*** allCells = (Cell***) malloc(sizeof(Cell*) * mapSize * mapSize);

	Cell* destCell = new Cell(dest, nullptr);
	destCell->g = 0;
	destCell->h = distance(pos, dest);

	allCells[dest.x][dest.y] = destCell;

	std::vector<Cell*> openSet = { destCell };

	while (!openSet.empty())
	{
		int current = 0;
		for (int i = 1; i < openSet.size(); i++)
			if (openSet[current]->g + openSet[current]->h > openSet[i]->g + openSet[i]->h)
				current = i;

		if (openSet[current]->pos.x == pos.x && openSet[current]->pos.y == pos.y) {
			free(allCells);
			return tracePath(openSet[current]);
		}

		Cell currentCell = *openSet[current];
		openSet.erase(std::next(openSet.begin(), current));

		sf::Vector2i* neighbours = getNeighboursOf(openSet[current], mapSize);

		for (int i = 0; i < sizeof(*neighbours) / sizeof(sf::Vector2i); i++)
		{
			if (allCells[neighbours[i].x][neighbours[i].y] == nullptr) {
				Cell newCell = Cell(neighbours[i], nullptr);
				newCell.h = distance(pos, neighbours[i]);
				allCells[neighbours[i].x][neighbours[i].y] = &newCell;
			}

			//TEMP: Currently every cell can access its direct neighbours 
			//regardless of obstacles or cliffs/cliff-faces

			Cell neighbour = *allCells[neighbours[i].x][neighbours[i].y];
			double temp_g = currentCell.g + 1;

			if (temp_g < neighbour.g)
			{
				neighbour.succ = &currentCell;
				neighbour.g = temp_g;
				if (std::find_if(openSet.begin(), openSet.end(), [lhs = &neighbour](Cell* rhs) { return rhs == lhs; }) != openSet.end())
					openSet.push_back(&neighbour);
			}
		}
	}

	//In case of failure
	free(allCells);
	return nullptr;
}

sf::Vector2i* Agent::getNeighboursOf(Cell* cell, const int& mapSize)
{
	//TEMP: This will need to be changed when the map is a quadtree, 
	//not a simple cartesian grid

	sf::Vector2i pos = cell->pos;

	//TODO: Handle map edges
	if (pos.x == 0 || pos.x == mapSize - 1 || pos.y == 0 || pos.y == mapSize - 1) {
		std::cerr << "Agent Pathfinding currently doesnt handle the map edges" << std::endl;
		return nullptr;
	}

	sf::Vector2i neighbours[] = {
		sf::Vector2i(pos.x + 1, pos.y),
		sf::Vector2i(pos.x - 1, pos.y),
		sf::Vector2i(pos.x, pos.y + 1),
		sf::Vector2i(pos.x, pos.y - 1),
	};

	return neighbours;
}

sf::Vector2i* Agent::tracePath(Cell* start)
{
	Cell* current = start;
	std::vector<sf::Vector2i> path = {start->pos};

	while (current->succ != nullptr)
	{
		path.push_back(current->succ->pos);
		current = current->succ;
	}

	return &path[0];
}

double Agent::distance(sf::Vector2i& v, sf::Vector2i& u) 
{
	//Return the square of the Euclidean distance. As long as we only use 
	//the squared values, we can save on computing the sqrt each time as
	//x^2 > y^2 implies that x > y for positive numbers x and y.
	//return (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y);

	return std::sqrt((v.x - u.x) * (v.x - u.x) + 
					 (v.y - u.y) * (v.y - u.y)
					);
}