#pragma once
#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include <SFML/Graphics.hpp>

class TheGreatWar {
protected:

public:
	static void SpawnRect(sf::Vector2f dimensions, sf::Vector2f position, sf::Color color, sf::RenderWindow& window, int outlineThickness = 5);

};