#pragma once
#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include <SFML/Graphics.hpp>

class TheGreatWar {
public:
	static void SpawnRect(sf::Vector2f dimensions, sf::Vector2f position, sf::Color color, sf::Color outlineColor, sf::RenderWindow& window, int outlineThickness = 5);
	static sf::RenderWindow window;
	static void InitializeNavMesh();

	static const int m_MeshSize = 2000;
	static const int m_CellSize = 100;
	sf::RectangleShape GridSquares[20][20];

private:


protected:

};