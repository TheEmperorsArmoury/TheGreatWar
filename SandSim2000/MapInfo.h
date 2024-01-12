#pragma once

#include <string>
#include "SFML/System/Vector2.hpp"

struct MapInfo {
    int     z;
    int     height;           // Integer from 0-9
    int     facing;           // Integer from 0-7
    bool    fogOfWar;

    std::string     terrain;   
    sf::FloatRect   rect;
};