#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
    initializeDefaultTerrainTexure();
    initializeGrassTerrainTextures();
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::initializeDefaultTerrainTexure()
{
    const std::string filePath = "../resources/images/Terrain/default.png";

    if (!defaultTerrainTexture.loadFromFile(filePath))
    {
        std::cerr << "Failed to load terrain texture from file: " << filePath << std::endl;
        return;
    }
}
void AnimationManager::initializeGrassTerrainTextures()
{
    const std::string presetFilePath = "../resources/images/Terrain/Grass/grass";
    for (int i = 1; i < 4; i++)
    {
        const std::string filePath = presetFilePath + std::to_string(i) + ".png";
        if (!GrassTexture[i - 1].loadFromFile(filePath))
        {
            std::cerr << "[TEXTURE][GRASS][FAILURE] File Path: " << filePath << std::endl;
            return;
        }
    }
}


void AnimationManager::renderSpriteMap(sf::RenderWindow* window)
{
    for (const sf::Sprite& sprite : spriteMap) {
        std::cout << sprite.getPosition().x << ":" << sprite.getPosition().y << '\n';
        window->draw(sprite);
    }
}

void AnimationManager::renderTerrainMap(sf::RenderWindow* window, GameState* gameState)
{
    sf::FloatRect viewBounds(0, 0, window->getSize().x, window->getSize().y);

    sf::Sprite sprite = sf::Sprite();
    GridGenerator gridGenerator;
    int centerOffsetX = window->getSize().x / 2;
    int OffsetY = 150;

    for (int i = 0; i < gameState->mapSize; i++)
    {
        for (int j = 0; j < gameState->mapSize; j++)
        {
            //Sets the texture of the sprite to the corresponding Grass tile
            sprite.setTexture(GrassTexture[gameState->getMapData()[i][j].height]);
            sprite.setTextureRect(sf::IntRect(0, 0, 100, gameState->getMapData()[i][j].height * 50 + 100));

            // Set the sprite position
            sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(i, j));
            
            // Y Transformations
            isometricPosition.y *= gameState->getMapData()[i][j].z;
            isometricPosition.y += OffsetY;
            isometricPosition.y -= 50 * gameState->getMapData()[i][j].height;

            // X Transformations
            isometricPosition.x += centerOffsetX;
            sprite.setPosition(isometricPosition);

            // Culling
            if(viewBounds.intersects(sprite.getGlobalBounds()))
                window->draw(sprite);
        }
    }
}