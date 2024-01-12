#include "GameState.h"

GameState::GameState()
{
    quadtree = QuadTree(sf::FloatRect(-WorldSize/2, -WorldSize/2, WorldSize, WorldSize), 0);
    clearAndInitializeMap();
}

GameState::~GameState()
{
}


void GameState::clearAndInitializeMap()
{
    GridGenerator gridGenerator;

    // Reset the old lists
    terrainMap.clear();
    quadtree.resize(sf::FloatRect(0, 0, WorldSize, WorldSize));

    // Fill the sprites
    for (int i = 0; i < mapSize; ++i)
    {
        for(int j = 0; j < mapSize; ++j)
        {
            MapInfo TerrainTile;
            TerrainTile.z = 1;          TerrainTile.height = rand() % 3;
            TerrainTile.facing = 0.0f;  TerrainTile.terrain = "default";

            // Terrain tile now needs to store the isometric rect
            sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(i, j));
            TerrainTile.rect = sf::FloatRect(isometricPosition, sf::Vector2f(100.0f, TerrainTile.height * 50 + 100));

            terrainMap.push_back(TerrainTile);

            quadtree.insert(&terrainMap.back(), TerrainTile.rect);
        }
    }
}
