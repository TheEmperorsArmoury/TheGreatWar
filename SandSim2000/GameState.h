#pragma once
#include "MapInfo.h"
#include "Agent.h"
#include <iostream>

class GameState
{
public:
	GameState();
	~GameState();

	MapInfo** getMapData() { return Map; }
	void clearAndInitializeMap();

	Agent* createAgentAt(const int&, const int&);

	static const int mapSize = 12;
private:
	MapInfo** Map = nullptr;
};

