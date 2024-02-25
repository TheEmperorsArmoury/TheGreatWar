#include "BattlefieldMap.h"
#include <cmath>
#include <iostream>

// Charlie Team: Please create a new method to initialise the subterranean map. It won't have any features, 
// just a plain grid of underground dirt sprites, no depth and no direction. Then ensure the GameStateManager
// uses the right map initiallisation when initiallising quad tree maps, ie tactical or subterranean.
// Also in the initSpriteMap() method, add a condition so it intialises the correct set of sprites based on the map, 
// tacticalMap or subterraneanMap.

void BattlefieldMap::initSubterraneanMap(unsigned int mapSize) {
  size = static_cast<int>(mapSize);

  depthMap = new int* [size];
  for (int y = 0; y < size; y++) {
    depthMap[y] = new int[size];
    for (int x = 0; x < size; x++) {
      depthMap[y][x] = 0;  // Constant depth for subterranean level as a placeholder dont judge
    }
  }

  // Create a single-value direction map (e.g., NONE)
  directionMap = new Direction* [size];
  for (int y = 0; y < size; y++) {
    directionMap[y] = new Direction[size];
    for (int x = 0; x < size; x++) {
      directionMap[y][x] = NONE;  // No specific direction for underground
    }
  }

  // Initialize the sprite map with dirt sprites
  initSpriteMap(true); // Pass true to use dirt sprites
}
void BattlefieldMap::initSpriteMap(bool isSubterranean) {
  spriteMap = new sf::Sprite** [size];
  for (int y = 0; y < size; y++) {
    spriteMap[y] = new sf::Sprite* [size];

    for (int x = 0; x < size; x++) {
      if (isSubterranean) {
        // Use dirt sprites for subterranean
        spriteMap[y][x] = dirt_spritesheet.getSprite(directionMap[y][x]);
      } else {
        // Use grass sprites for tactical maps (default behavior)
        spriteMap[y][x] = grass_spritesheet.getSprite(directionMap[y][x]);
      }
      spriteMap[y][x]->setTexture(isSubterranean ? dirt_spritesheet.texture : grass_spritesheet.texture);
    }
  }
}
//should work i think

void BattlefieldMap::initMap(unsigned int mapSize)
{
    size = static_cast<int>(mapSize);
    grass_spritesheet = SpriteManager("../resources/images/Terrain/grass/grass_spritesheet.png", 8, 2);

    // Chalie Team: I'm not sure the SpriteManager is correctly picking up this sprite, have a look at that please.
    // not sure, if it's wrong. tried to experiment with random pngs looks like it works
    dirt_spritesheet = SpriteManager("../resources/images/Terrain/dirt/dirt_spritesheet.png", 8, 2);
        
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
