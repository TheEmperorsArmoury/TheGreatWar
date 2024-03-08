  #include "GridGenerator.h"
#include <iostream>


GridGenerator::GridGenerator() {}

sf::Vector2f GridGenerator::cartesianToIsometricTransform(const sf::Vector2f& cartesianPosition)
{
    sf::Vector2f isometricPosition;
    const float spriteDimension = 50.0f;
    const float A = cartesianPosition.x * 1.0f * spriteDimension;
    const float B = cartesianPosition.y * -1.0f * spriteDimension;
    const float C = cartesianPosition.x * 0.5f * spriteDimension;
    const float D = cartesianPosition.y * 0.5f * spriteDimension;
    isometricPosition.x = A + B;
    isometricPosition.y = C + D;
    return isometricPosition;
}

sf::Vector2f GridGenerator::isometricToCartesianTransform(const sf::Vector2f& isometricPosition)
{
    sf::Vector2f cartesianPosition;
    const float spriteDimension = 50.0f;
    float det = 1.0f / (1 * 0.5 - 0 * -1);
    cartesianPosition.x = (((isometricPosition.x + isometricPosition.y * 2) / 2) - 25) / 50;
    cartesianPosition.y = (((det * (-isometricPosition.x * 0.5 + isometricPosition.y * 1)) - 50) / 100) - 1;
    return cartesianPosition;
}


sf::Vector2f GridGenerator::mouseToIsometric(const sf::Vector2i& mouseCoords)
{
    const float spriteDimension = 50.0f;
    float det = 1.0f / (1 * 0.5 - 0 * -1);
    sf::Vector2f isometricCoords;
    isometricCoords.x = (mouseCoords.x / spriteDimension) - 8 * (mouseCoords.y / spriteDimension);
    isometricCoords.y = 8 * (mouseCoords.x / spriteDimension) + (mouseCoords.y / spriteDimension);
    return isometricCoords;
}


sf::Vector2f GridGenerator::cellSelector(const sf::Vector2f cartesianCell, int corner)
{
    sf::Vector2f selectedCell;
    const sf::Vector2f origin = { 1,0 };
    selectedCell.x = (cartesianCell.y - origin.y) + (cartesianCell.x - origin.x);
    selectedCell.y = (cartesianCell.y - origin.y) - (cartesianCell.x - origin.x);
    if (corner == 1) selectedCell.x = selectedCell.x - 1;
    if (corner == 2) selectedCell.y = selectedCell.y - 1;
    if (corner == 3) selectedCell.x = selectedCell.x + 1;
    if (corner == 4) selectedCell.y = selectedCell.y + 1;
    return selectedCell;
}

sf::Vector2f GridGenerator::mouseCellCalc(const sf::Vector2f mouseCoord)
{
    sf::Vector2f mouseCellPosition;
    int tileWidth = 100;
    int tileHeight = 50;
    mouseCellPosition.x = ((int)mouseCoord.x - 50) % tileWidth;
    mouseCellPosition.y = (int)mouseCoord.y % tileHeight;
    return mouseCellPosition;
}

int GridGenerator::isInsideTriangle(sf::Vector2f mousePos)
{
    sf::Vector2f A(50.f, 0.f);
    sf::Vector2f B(100.f, 25.f);
    sf::Vector2f C(50.f, 50.f);
    sf::Vector2f D(0.f, 25.f);

    sf::Vector2f directionAD = A - D;
    sf::Vector2f vectorToMouseAD = mousePos - A;
    float crossProductAD = directionAD.x * vectorToMouseAD.y - directionAD.y * vectorToMouseAD.x;
    if (crossProductAD <= 0.f) return 1;

    sf::Vector2f directionAB = A - B;
    sf::Vector2f vectorToMouseAB = mousePos - A;
    float crossProductAB = directionAB.x * vectorToMouseAB.y - directionAB.y * vectorToMouseAB.x;
    if (crossProductAB > 0.f) return 2;

    sf::Vector2f directionBC = B - C;
    sf::Vector2f vectorToMouseBC = mousePos - B;
    float crossProductBC = directionBC.x * vectorToMouseBC.y - directionBC.y * vectorToMouseBC.x;
    if (crossProductBC > 0.f) return 3;

    sf::Vector2f directionCD = C - D;
    sf::Vector2f vectorToMouseCD = mousePos - C;
    float crossProductCD = directionCD.x * vectorToMouseCD.y - directionCD.y * vectorToMouseCD.x;
    if (crossProductCD > 0.f) return 4;

    return 0;
}

sf::Vector2f GridGenerator::isometricToScreenPosition(sf::Vector2f isometricPosition)
{
    const float tileWidth = 100.0f;
    const float tileHeight = 50.0f;
    float screenX = (isometricPosition.x - isometricPosition.y) * 0.5f * tileWidth;
    float screenY = (isometricPosition.x + isometricPosition.y) * 0.5f * tileHeight;
    sf::Vector2f screenPosition(screenX, screenY);
    return screenPosition;
}