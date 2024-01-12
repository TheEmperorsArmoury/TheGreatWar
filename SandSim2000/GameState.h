#pragma once

#include <iostream>
#include <list>

#include "SFML/Graphics.hpp"

#include "MapInfo.h"
#include "QuadTree.h"
#include "GridGenerator.h"

class GameState
{
public:
	GameState();
	~GameState();

	QuadTree* getQuadtreeInstance() { return &quadtree; }
	void clearAndInitializeMap();

	static const int mapSize = 500;
private:
	QuadTree quadtree;

	std::list<MapInfo> terrainMap;

	const float WorldSize = 10000.0f;
};

