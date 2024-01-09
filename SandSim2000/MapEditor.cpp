#include "MapEditor.h"
#include <iostream>
#include <string>
#include <map>

const std::string resourcesPath = "..\\resources\\";

MapEditor::MapEditor()
    : Map(nullptr) {
}

void MapEditor::createSpriteMap()
{
    GridGenerator gridGenerator;
    spriteMap.clear();
    spriteMap.resize(mapSize, std::vector<sf::Sprite>(mapSize));
    int centerXOffset = 725;

    const std::string& terrainType = "default";
<<<<<<< HEAD
    const std::string filePath = resourcesPath + "images\\Terrain\\" + terrainType + ".png";
=======
    const std::string filePath = "A:\\C++\\TheGreatWar\\resources\\images\\Terrain\\" + terrainType + ".png";
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e

    if (!terrainTexture.loadFromFile(filePath))
    {
        std::cerr << "Failed to load terrain texture from file: " << filePath << std::endl;
        return;
    }

    for (int i = 0; i < mapSize; ++i)
    {
        for (int j = 0; j < mapSize; ++j)
        {
            sf::Sprite& sprite = spriteMap[i][j];
            sprite.setTexture(terrainTexture);
            MapInfo& mapInfo = Map[i][j];
            sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(i, j));
            isometricPosition.y *= mapInfo.z;
            isometricPosition.x += centerXOffset;
            sprite.setPosition(isometricPosition);
        }
    }
}


void MapEditor::initialiseNewMap()
{
    if (Map != nullptr) {
        for (int i = 0; i < mapSize; ++i) {
            delete[] Map[i];
            
        }
        delete[] Map;
    }
    Map = new MapInfo * [mapSize];
    for (int i = 0; i < mapSize; ++i) {
        Map[i] = new MapInfo[mapSize];

        for (int j = 0; j < mapSize; ++j) {
            Map[i][j].z = 1;
            Map[i][j].facing = 0.0f;
            Map[i][j].terrain = "default";
        }
    }
}

void MapEditor::heightEditor()
{
    initialiseNewMap();
    createSpriteMap();
}


void MapEditor::addSubtractHeight(sf::Event& event)
{
    if (event.mouseButton.button == sf::Mouse::Left) std::cout << "Left Click Detected" << std::endl;
    else if (event.mouseButton.button == sf::Mouse::Right) std::cout << "Right Click Detected" << std::endl;

    GridGenerator gridGen; 
    sf::Vector2f clickPosition = { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
    sf::Vector2f isoCoords = gridGen.mouseToIsometric(sf::Vector2i(clickPosition));
    sf::Vector2f clickedCell = gridGen.mouseCellCalc(isoCoords);
}

void MapEditor::buttonHandler(sf::RenderWindow& window, sf::Event& event, sf::Font& font)
{
    sf::Texture heightEditorButtonTexture;
<<<<<<< HEAD
    if (!heightEditorButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\MapEditorImages\\heightEditorButton.png")) {
=======
    if (!heightEditorButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\MapEditorImages\\heightEditorButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite heightEditorButtonSprite(heightEditorButtonTexture);
    heightEditorButtonSprite.setPosition(1685.0f, 200.0f);

    sf::Texture terrainEditorButtonTexture;
<<<<<<< HEAD
    if (!terrainEditorButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\MapEditorImages\\terrainEditorButton.png")) {
=======
    if (!terrainEditorButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\MapEditorImages\\terrainEditorButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite terrainEditorButtonSprite(terrainEditorButtonTexture);
    terrainEditorButtonSprite.setPosition(1685.0f, 320.0f);

    sf::Texture sceneryEditorButtonTexture;
<<<<<<< HEAD
    if (!sceneryEditorButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\MapEditorImages\\sceneryEditorButton.png")) {
=======
    if (!sceneryEditorButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\MapEditorImages\\sceneryEditorButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite sceneryEditorButtonSprite(sceneryEditorButtonTexture);
    sceneryEditorButtonSprite.setPosition(1685.0f, 440.0f);

    sf::Texture newMapButtonTexture;
<<<<<<< HEAD
    if (!newMapButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\MapEditorImages\\newMapButton.png")) {
=======
    if (!newMapButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\MapEditorImages\\newMapButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite newMapButtonSprite(newMapButtonTexture);
    newMapButtonSprite.setPosition(1685.0f, 560.0f);

    sf::Texture saveMapButtonTexture;
<<<<<<< HEAD
    if (!saveMapButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\MapEditorImages\\saveMapButton.png")) {
=======
    if (!saveMapButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\MapEditorImages\\saveMapButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite saveMapButtonSprite(saveMapButtonTexture);
    saveMapButtonSprite.setPosition(1685.0f, 680.0f);

    sf::Texture loadMapButtonTexture;
<<<<<<< HEAD
    if (!loadMapButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\MapEditorImages\\loadMapButton.png")) {
=======
    if (!loadMapButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\MapEditorImages\\loadMapButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite loadMapButtonSprite(loadMapButtonTexture);
    loadMapButtonSprite.setPosition(1685.0f, 800.0f);

    sf::Texture closeMapButtonTexture;
<<<<<<< HEAD
    if (!closeMapButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\MapEditorImages\\closeMapButton.png")) {
=======
    if (!closeMapButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\MapEditorImages\\closeMapButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load close button texture!" << std::endl;
        return;
    }
    sf::Sprite closeMapButtonSprite(closeMapButtonTexture);
    closeMapButtonSprite.setPosition(1685.0f, 920.0f);

    sf::Texture rightBackgroundTexture;
<<<<<<< HEAD
    if (!rightBackgroundTexture.loadFromFile(resourcesPath + "images\\Utilities\\rightMenuBG.png")) {
=======
    if (!rightBackgroundTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\rightMenuBG.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite rightBackgroundSprite(rightBackgroundTexture);
    rightBackgroundSprite.setPosition(1580.0f, 0.0f);

    sf::Texture bottomBackgroundTexture;
<<<<<<< HEAD
    if (!bottomBackgroundTexture.loadFromFile(resourcesPath + "images\\Utilities\\bottomMenuBG.png")) {
=======
    if (!bottomBackgroundTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\bottomMenuBG.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite bottomBackgroundSprite(bottomBackgroundTexture);
    bottomBackgroundSprite.setPosition(0.0f, 710.0f);

    sf::Texture addHeightButtonTexture;
<<<<<<< HEAD
    if (!addHeightButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\menuButton.png")) {
=======
    if (!addHeightButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\menuButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite addHeightButtonSprite(addHeightButtonTexture);
    addHeightButtonSprite.setPosition(100.0f, 960.0f);

    sf::Texture removeHeightButtonTexture;
<<<<<<< HEAD
    if (!removeHeightButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\menuButton.png")) {
=======
    if (!removeHeightButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\menuButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite removeHeightButtonSprite(removeHeightButtonTexture);
    removeHeightButtonSprite.setPosition(400.0f, 960.0f);


    sf::Texture backButtonTexture;
<<<<<<< HEAD
    if (!backButtonTexture.loadFromFile(resourcesPath + "images\\Utilities\\menuButton.png")) {
=======
    if (!backButtonTexture.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Images\\Utilities\\menuButton.png")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    sf::Sprite backButtonSprite(backButtonTexture);
    backButtonSprite.setPosition(700.0f, 960.0f);

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (newMapButtonSprite.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            buttonStates.newMap = true;
        }
    }

    window.draw(rightBackgroundSprite);
    window.draw(bottomBackgroundSprite);
    window.draw(heightEditorButtonSprite);
    window.draw(terrainEditorButtonSprite);
    window.draw(sceneryEditorButtonSprite);
    window.draw(newMapButtonSprite);
    window.draw(saveMapButtonSprite);
    window.draw(loadMapButtonSprite);
    window.draw(closeMapButtonSprite);
    window.draw(addHeightButtonSprite);
    window.draw(removeHeightButtonSprite);
    window.draw(backButtonSprite);
}

void MapEditor::viewPortRenderer(sf::RenderWindow& window, const sf::Event& event)
{
    sf::FloatRect testBounds(0, 0, 1650, 900);
    int edgeThreshold = 75;
    int maxScrollSpeed = 50;

    int tileWidth = 100;
    int tileHeight = 100;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    int distanceX = std::max(0, edgeThreshold - std::abs(mousePos.x - edgeThreshold));
    int distanceY = std::max(0, edgeThreshold - std::abs(mousePos.y - edgeThreshold));

    int scrollSpeedX = maxScrollSpeed - (maxScrollSpeed * distanceX / edgeThreshold);
    int scrollSpeedY = maxScrollSpeed - (maxScrollSpeed * distanceY / edgeThreshold);

    if (mousePos.x < edgeThreshold) {
        for (auto& row : spriteMap) {
            for (sf::Sprite& sprite : row) {
                sprite.move(scrollSpeedX, 0);
            }
        }
        mapOriginScrollOffset.x += scrollSpeedX;
    }
    if (mousePos.x > (window.getSize().x - edgeThreshold)) {
        for (auto& row : spriteMap) {
            for (sf::Sprite& sprite : row) {
                sprite.move(-scrollSpeedX, 0);
            }
        }
        mapOriginScrollOffset.x -= scrollSpeedX;
    }
    if (mousePos.y < edgeThreshold) {
        for (auto& row : spriteMap) {
            for (sf::Sprite& sprite : row) {
                sprite.move(0, scrollSpeedY);
            }
        }
        mapOriginScrollOffset.y += scrollSpeedY;
    }
    if (mousePos.y > (window.getSize().y - edgeThreshold)) {
        for (auto& row : spriteMap) {
            for (sf::Sprite& sprite : row) {
                sprite.move(0, -scrollSpeedY);
            }
        }
        mapOriginScrollOffset.y -= scrollSpeedY;
    }

    for (const auto& row : spriteMap) {
        for (const sf::Sprite& sprite : row) {
            if (testBounds.intersects(sprite.getGlobalBounds())) {
                window.draw(sprite);
            }
        }
    }
}

void MapEditor::run(sf::RenderWindow& window)
{
    initialiseNewMap();
    createSpriteMap();
    sf::Font font;
<<<<<<< HEAD
    if (!font.loadFromFile(resourcesPath + "fonts\\WorldAtWar.ttf")) {
=======
    if (!font.loadFromFile("A:\\C++\\TheGreatWar\\resources\\Fonts\\WorldAtWar.ttf")) {
>>>>>>> 42b05533fdf2c04a2d558760a02721f64c44398e
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        
            if (buttonStates.heightEditor && event.type == sf::Event::MouseButtonPressed) {
                addSubtractHeight(event);
            }
        }
        if (buttonStates.newMap)
        {
            buttonStates.heightEditor = true;
            buttonStates.newMap = false;
        }
        
        window.clear(sf::Color::Black);
        std::cout << "Origin scroll offset PX , X: " << mapOriginScrollOffset.x << ", Y: " << mapOriginScrollOffset.y << std::endl;
       
        viewPortRenderer(window, event);
        buttonHandler(window, event, font);
        window.display();
    }
}