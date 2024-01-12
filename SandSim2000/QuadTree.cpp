#include "QuadTree.h"

namespace sf {
    bool rectContains(const sf::FloatRect rect1, const sf::FloatRect rect2)
    {
        return (rect2.getPosition().x >= rect1.getPosition().x) && (rect2.getPosition().x + rect2.getSize().x < rect1.getPosition().x + rect1.getPosition().x) &&
            (rect2.getPosition().y >= rect1.getPosition().y) && (rect2.getPosition().y + rect2.getSize().y < rect1.getPosition().y + rect1.getPosition().y);
    }
}

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
    if(depth + 1 < MAX_DEPTH)
    {
        for (int i = 0; i < 4; i++)
        {
            if (sf::rectContains(childQuadRect[i], itemSize))
            {
                if (!childQuad[i])
                    childQuad[i] = std::make_shared<QuadTree>(childQuadRect[i], depth + 1);
                childQuad[i]->insert(item, itemSize);
                return;

            }
        }
    }
    //if gotten to this point, the item didnt fit in any children
    //so add it to this quads list of items
    quadItems.push_back(item);
}

std::list<MapInfo*> QuadTree::search(sf::FloatRect searchArea)
{
    std::list<MapInfo*> listItems;
    searchQuad(searchArea, &listItems);
    return listItems;
}

void QuadTree::searchQuad(sf::FloatRect searchArea, std::list<MapInfo*>* coveredItems)
{
    for (int i = 0; i < quadItems.size(); i++)
    {
        if (searchArea.intersects(quadItems[i]->rect))
            coveredItems->push_back(quadItems[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        if (childQuad[i])
        {
            if (sf::rectContains(searchArea, childQuadRect[i]))
                childQuad[i]->items(coveredItems);

            else if (childQuadRect[i].intersects(quadRect))
                childQuad[i]->searchQuad(searchArea, coveredItems);
                
        }
    }
}

void QuadTree::items(std::list<MapInfo*>* listItems)
{
    // Chuck all this quad items in the list
    for (int i = 0; i < quadItems.size(); i++)
        listItems->push_back(quadItems[i]);

    // Chuck all the child quad items in the list
    for (int i = 0; i < 4; i++)
    {
        if (childQuad[i])
            childQuad[i]->items(listItems);
    }
}

std::list<MapInfo*> QuadTree::items()
{
    std::list<MapInfo*> listItems;
    items(&listItems);
    return listItems;
}