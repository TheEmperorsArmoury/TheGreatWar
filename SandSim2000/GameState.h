#pragma once

#include <list>

#include "SFML/Graphics.hpp"

#include "MapInfo.h"

class GameState
{
public:
	GameState();
	~GameState();

	MapInfo** getMapData() { return Map; }
	void clearAndInitializeMap();

	static const int mapSize = 12;
private:
	MapInfo** Map = nullptr;

	std::list<MapInfo> terrainMap;
};

