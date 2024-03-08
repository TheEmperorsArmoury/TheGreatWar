#include "BattlefieldMap.h"
#include <cmath>
#include <iostream>

void BattlefieldMap::initMap(unsigned int mapSize)
{
    size = static_cast<int>(mapSize);
    grass_spritesheet = SpriteManager::GetInstance()->GetSpriteSheet("GrassTerrain");
  
    initDepthMap();
    initDirectionMap();
    initSpriteMap();
}

void BattlefieldMap::initDepthMap()
{
    depthMap = new int* [size];

    depthMap[0] = new int[size]     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    depthMap[1] = new int[size]     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    depthMap[2] = new int[size]     {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[3] = new int[size]     {0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[4] = new int[size]     {0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[5] = new int[size]     {0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[6] = new int[size]     {0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[7] = new int[size]     {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[8] = new int[size]     {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 0, 0};
    depthMap[9] = new int[size]     {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 0, 0};
    depthMap[10] = new int[size]    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[11] = new int[size]    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[12] = new int[size]    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[13] = new int[size]    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
    depthMap[14] = new int[size]    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    depthMap[15] = new int[size]    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

}


void BattlefieldMap::initDirectionMap()
{
    directionMap = new Direction * [size];

    directionMap[0] = new Direction[size]   { F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F };
    directionMap[1] = new Direction[size]   { F, NE, E, E, E, E, E, E, E, E, E, E, E, E, SE, F };
    directionMap[2] = new Direction[size]   { F, N, NE, E, E, SE, F, F, F, F, F, F, F, F, S, F };
    directionMap[3] = new Direction[size]   { F, N, N, F, F, S, F, F, F, F, F, F, F, F, S, F };
    directionMap[4] = new Direction[size]   { F, N, N, F, F, S, F, F, F, F, F, F, F, F, S, F };
    directionMap[5] = new Direction[size]   { F, N, N, F, F, S, F, F, F, F, F, F, F, F, S, F };
    directionMap[6] = new Direction[size]   { F, N, N, F, F, S, F, F, F, F, F, F, F, F, S, F };
    directionMap[7] = new Direction[size]   { F, N, NW, W, W, SW, F, F, F, NE, E, E, E, SE, S, F };
    directionMap[8] = new Direction[size]   { F, N, F, F, F, F, F, F, F, N, F, F, F, S, S, F };
    directionMap[9] = new Direction[size]   { F, N, F, F, F, F, F, F, F, N, F, F, F, S, S, F };
    directionMap[10] = new Direction[size]  { F, N, F, F, F, F, F, F, F, NW, W, W, W, SW, S, F };
    directionMap[11] = new Direction[size]  { F, N, F, F, F, F, F, F, F, F, F, F, F, F, S, F };
    directionMap[12] = new Direction[size]  { F, N, F, F, F, F, F, F, F, F, F, F, F, F, S, F };
    directionMap[13] = new Direction[size]  { F, N, F, F, F, F, F, F, F, F, F, F, F, F, S, F };
    directionMap[14] = new Direction[size]  { F, NW, W, W, W, W, W, W, W, W, W, W, W, W, SW, F };
    directionMap[15] = new Direction[size]  { F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F };
}
    
int BattlefieldMap::testLocation(int x, int y, int height)
{
    if (x > 0 && x < size - 1 && y > 0 && y < size - 1)
        return depthMap[y][x] - height;
    return 0;
}

void BattlefieldMap::initSpriteMap()
{
    spriteMap = new sf::Sprite ** [size];
    for (int y = 0; y < size; y++)
    {
        spriteMap[y] = new sf::Sprite * [size];

        for (int x = 0; x < size; x++)
        {
            spriteMap[y][x] = grass_spritesheet.getSprite(directionMap[y][x]);
            spriteMap[y][x]->setTexture(grass_spritesheet.texture);
        }
    }
}


BattlefieldMap::~BattlefieldMap()
{
    for (int i = 0; i < size; i++) {
        delete[] depthMap[i];
        delete[] directionMap[i];
        delete[] spriteMap[i];
    }
    delete[] depthMap;
    delete[] directionMap;
    delete[] spriteMap;
}
