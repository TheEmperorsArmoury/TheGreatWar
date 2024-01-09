#include "GameState.h"

GameState::GameState()
{
    clearAndInitializeMap();
}

GameState::~GameState()
{
}


void GameState::clearAndInitializeMap()
{
    if (Map != nullptr) {
        for (int i = 0; i < mapSize; ++i) {
            delete[] Map[i];

        }
        delete[] Map;
    }
    Map = new MapInfo * [mapSize];
    for (int i = 0; i < mapSize; ++i) {
        Map[i] = new MapInfo[mapSize];

        for (int j = 0; j < mapSize; ++j) {
            Map[i][j].z = 1;
            Map[i][j].height = rand() & 3 - 1;
            Map[i][j].facing = 0.0f;
            Map[i][j].terrain = "default";
        }
    }
}
