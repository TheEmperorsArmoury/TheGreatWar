#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "MapInfo.h"
struct Cell
{
	Cell* pred;
	sf::Vector2i pos;

	double g, h;

	Cell(sf::Vector2i& newPos, double newH)
		: pos(newPos), pred(nullptr), g(DBL_MAX), h(newH) {}

	bool operator==(const Cell& rhs) const
	{
		return pos == rhs.pos;
	}

	bool operator==(const sf::Vector2i& rhs) const
	{
		return pos == rhs;
	}
};

class MovementManager
{
public:
	MovementManager(MapInfo**, const int&);
	~MovementManager();

	std::vector<sf::Vector2i> findPath(sf::Vector2i, sf::Vector2i);
private:
	void initialiseMapCells();

	std::vector<sf::Vector2i> tracePath(Cell&);
	std::vector<sf::Vector2i> getNeighboursOf(Cell&);
	double distance(sf::Vector2i&, sf::Vector2i&);

	Cell*** mapCells;
	const int mapSize;
};