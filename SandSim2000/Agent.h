#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

struct Cell
{
	Cell* succ;
	sf::Vector2i pos;

	double g, h;

	Cell()
		: pos(sf::Vector2i(INT32_MAX, INT32_MAX)), succ(nullptr), g(DBL_MAX), h(DBL_MAX) {}

	Cell(sf::Vector2i& newPos, Cell* newSucc) 
		: pos(newPos), succ(newSucc), g(DBL_MAX), h(DBL_MAX) {}

	bool operator==(const Cell& rhs) const
	{
		return pos == rhs.pos;
	}
};

class Agent 
{
public:
	Agent(sf::Vector2i);
	~Agent();

	void setPosition(sf::Vector2i& newPos) { pos = newPos; }
	sf::Vector2i getPosition() { return pos; }

	sf::Vector2i* findPath(sf::Vector2i, const int&);
private:
	sf::Vector2i* tracePath(Cell*);
	double distance(sf::Vector2i&, sf::Vector2i&);
	sf::Vector2i* getNeighboursOf(Cell*, const int&);

	sf::Vector2i pos;
};