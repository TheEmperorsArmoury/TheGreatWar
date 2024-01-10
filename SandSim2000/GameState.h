#pragma once
#include "MapInfo.h"
#include <iostream>

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
};

