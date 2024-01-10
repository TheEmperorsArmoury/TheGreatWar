#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "GridGenerator.h"
#include "GameState.h"
#include "MapInfo.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	void renderSpriteMap(sf::RenderWindow* window);
	void renderTerrainMap(sf::RenderWindow* window, GameState* gameState);
private:
	void initializeDefaultTerrainTexure();
	void initializeGrassTerrainTextures();
	

	std::vector<sf::Sprite> spriteMap;
	sf::Texture defaultTerrainTexture;

	sf::Texture GrassTexture[3];
};

