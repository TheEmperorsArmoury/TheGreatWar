#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "MapInfo.h"
struct Node
{
	Node* pred;
	sf::Vector2i pos;

	double g, h;

	Node(sf::Vector2i& newPos, double newH)
		: pos(newPos), pred(nullptr), g(DBL_MAX), h(newH) {}

	bool operator==(const Node& rhs) const
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
	MovementManager(const int&);
	~MovementManager();

	std::vector<sf::Vector2i> AStarPathFind(sf::Vector2i, sf::Vector2i);
private:
	void initialiseMapNodes();

	std::vector<sf::Vector2i> retracePath(Node&);
	std::vector<sf::Vector2i> getNeighboursOf(Node&) const;
	double euclideanDistance(sf::Vector2i&, sf::Vector2i&) const;

	Node*** mapNodes;
	const int mapSize;
};