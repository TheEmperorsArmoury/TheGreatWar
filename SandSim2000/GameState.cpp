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
    terrainMap.clear();
    if (Map != nullptr) {
        for (int i = 0; i < mapSize; ++i) {
            delete[] Map[i];

        }
        delete[] Map;
    }

    //Fill the sprites
    Map = new MapInfo* [mapSize];
    for (int i = 0; i < mapSize; ++i)
    {
        Map[i] = new MapInfo[mapSize];
        for(int j = 0; j < mapSize; ++j)
        {
            MapInfo TerrainTile;
            TerrainTile.z = 1;          TerrainTile.height = rand() % 3;
            TerrainTile.facing = 0.0f;  TerrainTile.terrain = "default";
            TerrainTile.position = sf::Vector2f(i, j);
            terrainMap.push_back(TerrainTile);

            Map[i][j] = terrainMap.back();
        }
    }
}
