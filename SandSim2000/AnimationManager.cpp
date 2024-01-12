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
    QuadTree* quadtree = gameState->getQuadtreeInstance();

    int centerOffsetX = window->getSize().x / 2;
    int OffsetY = -1000;

    viewBounds.left -= centerOffsetX;
    viewBounds.top -= OffsetY;

    std::list<MapInfo*> items = quadtree->search(viewBounds);

    for (const auto* object : items)
    {
        sprite.setTexture(GrassTexture[object->height]);
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(object->rect.getSize())));

        sf::Vector2f isometricPosition = object->rect.getPosition();

        isometricPosition.y *= object->z;
        isometricPosition.y += OffsetY;
        isometricPosition.y -= 50 * object->height;

        isometricPosition.x += centerOffsetX;
            
        sprite.setPosition(isometricPosition);

        window->draw(sprite);
    }
}