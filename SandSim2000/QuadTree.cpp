#include "QuadTree.h"

QuadTree::QuadTree(sf::FloatRect size, unsigned int Depth)
{
    depth = Depth;
    resize(size);
}

void QuadTree::resize(sf::FloatRect size)
{
    clear();

    quadRect = size;
    sf::Vector2f childSize = sf::Vector2f(quadRect.width / 2, quadRect.height / 2);

    //Set the rect of the child quads
    childQuadRect =
    {
        sf::FloatRect(quadRect.getPosition(), childSize),                                                           //Top       Left
        sf::FloatRect(quadRect.getPosition().x + childSize.x, quadRect.getPosition().y, childSize.x, childSize.y),  //Top       Right
        sf::FloatRect(quadRect.getPosition().x, quadRect.getPosition().y + childSize.y, childSize.x, childSize.y),  //Bottom    Left
        sf::FloatRect(quadRect.getPosition()+  childSize, childSize)                                                //Bottom    Right
    };
}

void QuadTree::clear()
{
    quadItems.clear();
    for (int i = 0; i < 4; i++)
    {
        //if the child quad exists, clean it
        if (childQuad[i])
            childQuad[i]->clear();
        childQuad[i].reset();
    }
}

unsigned int QuadTree::size()
{
    unsigned int count = quadItems.size();
    for (int i = 0; i < 4; i++)
    {
        if (childQuad[i])
            count += childQuad[i]->size();
    }
    return count;
}

void QuadTree::insert(MapInfo* item, sf::FloatRect itemSize)
{
}

std::list<MapInfo*> QuadTree::search(sf::FloatRect searchArea)
{
    return std::list<MapInfo*>();
}

void QuadTree::searchQuad(sf::FloatRect searchArea, std::list<MapInfo*> coveredItems)
{
}

std::list<MapInfo*> QuadTree::items()
{
    return std::list<MapInfo*>();
}
