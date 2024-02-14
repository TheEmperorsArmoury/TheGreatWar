#include "GameStateManager.h"

#define CELLSIZE 100

GameStateManager::GameStateManager(unsigned int numCells) {
    initializeBattlefieldVector(numCells);
}

// Charlie Team: Right now this code only initialises and generates 1 quadTree,
// pleaes change this class so the tacticalMap and subterraneanMap will both get initialised and generated.
// Try to build in such a way that can have the strategicMap initialised and genreated too, later.
// So maybe change the method names to initialseMap and generateMap,
// then pass the relevant map in as an argument if possible, just an idea, follw a better way if you find one.

// Regardless of which map, all iterators stored in the quad trees point to objects all stored in the battlefieldVector. 

void GameStateManager::initialiseQuadTree(unsigned int battlefieldSize, unsigned int& index) {
    battlefieldMap.initMap(static_cast<unsigned int>(battlefieldSize / 100));
    state.quadTree = new QuadTree(sf::IntRect(0, 0, battlefieldSize, battlefieldSize), 0);
    generateQuadTree((QuadTree*)state.quadTree, index);

}

void GameStateManager::generateQuadTree(QuadTree* root, unsigned int& index) {
    float size = root->quadRect.getSize().x / 2;
    if (size > CELLSIZE) {

        std::array<QuadTree*, 4> children;

        for (int i = 0; i < 4; i++) {

            children[i] = new QuadTree(
                sf::IntRect(
                    root->quadRect.getPosition().x + size * (i % 2),
                    root->quadRect.getPosition().y + size * ((int)(i > 1)),
                    size, size
                ), 
                root->depth + 1
            );

            generateQuadTree((QuadTree*)children[i], index);
        }

        root->children = children;
    } else {

        std::array<QuadTree*, 4> children;

        for (int i = 0; i < 4; i++) {
            int x = root->quadRect.getPosition().x + size * (i % 2);
            int y = root->quadRect.getPosition().y + size * ((int)(i > 1)); 

            state.BattlefieldVector[index] = generateCell(x / CELLSIZE, y/CELLSIZE);

            std::vector<BattlefieldCell>::iterator iter = state.BattlefieldVector.begin() + (index++);

            children[i] = new QuadTreeLeaf(
                sf::IntRect(x, y, size, size), 
                root->depth + 1,
                iter
            );
        }

        root->children = children;
    }
}

BattlefieldCell GameStateManager::generateCell(int x, int y)
{
    TerrainTile newTerr;
    newTerr.depth = battlefieldMap.getHeightAtPosition({ x, y});
    newTerr.facing = 0;
    newTerr.terrain = "default";

    BattlefieldCell newCell;
    newCell.x = x;
    newCell.y = y;
    newCell.terrain = newTerr;
    newCell.sprite = battlefieldMap.getSpriteAtPosition({ x, y });
    newCell.YOffset = battlefieldMap.getHeightAtPosition({ x, y }) * CELLSIZE / 4;

    return newCell;
}

void GameStateManager::initializeBattlefieldVector(unsigned int numCells) 
{
    state.BattlefieldVector.clear();
    state.BattlefieldVector.resize(numCells); 
    unsigned int index = 0;
    initialiseQuadTree(static_cast<int>(std::floor(std::sqrt(numCells))) * 100, index);
}

