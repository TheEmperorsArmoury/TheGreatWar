#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class Agent 
{
public:
	Agent(sf::Vector2i);
	~Agent();

	void setPosition(sf::Vector2i& newPos) { pos = newPos; }
	sf::Vector2i getPosition() { return pos; }
private:
	sf::Vector2i pos;
};