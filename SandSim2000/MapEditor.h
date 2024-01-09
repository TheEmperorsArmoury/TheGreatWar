#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "GridGenerator.h"
#include "AssetCRUDManager.h"
#include "MapInfo.h"

struct ButtonStates {
    bool heightEditor;
    bool terrainEditor;
    bool sceneryEditor;
    bool newMap;
    bool saveMap;
    bool loadMap;
    bool closeMap;
    bool addRemoveHeight;
    
    bool isometricPerspective;
    
    ButtonStates()
        :heightEditor(false),
        terrainEditor(false),
        sceneryEditor(false),
        newMap(false),
        saveMap(false),
        loadMap(false),
        closeMap(false),
        addRemoveHeight(false),
        isometricPerspective(false) {}
};

class MapEditor
{
public:
    MapEditor();

    void handleEditorSwitching(ButtonStates& buttonStates);
    void heightEditor();
    void addSubtractHeight(sf::Event& event);
    void initialiseNewMap();
    void buttonHandler(sf::RenderWindow& window, sf::Event& event, sf::Font& font);
    std::map<std::string, sf::Texture> loadAndCacheTextures(MapInfo** Map, int mapSize);
    void createSpriteMap();
    void viewPortRenderer(sf::RenderWindow& window, const sf::Event& event);
    void run(sf::RenderWindow& window);

private:
    static const int mapSize = 12;
    sf::Vector2f mapOriginScrollOffset;
    sf::Texture terrainTexture;
    sf::Sprite terrainSprite;
    MapInfo** Map;
    std::vector<std::vector<sf::Sprite>> spriteMap;
    ButtonStates buttonStates;
};