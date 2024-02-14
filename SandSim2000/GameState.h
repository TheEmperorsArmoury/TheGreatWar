#pragma once
#include <vector>
#include "BattlefieldCell.h"
#include "QuadTree.h"

class GameState {
public:
    std::vector<BattlefieldCell> BattlefieldVector;
    QuadTree* quadTree = nullptr;

    // Charlie Team: Please change the quadTree member property to tacticalMap
    // and add the subterraneanMap. Don't worry about the strategicMap, that will come later. 

    //QuadTree* strategicMap = nullptr;
    //QuadTree* tacticalMap = nullptr;
    //QuadTree* subterraneanMap = nullptr;
};



