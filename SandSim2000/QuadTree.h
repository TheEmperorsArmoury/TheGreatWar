#pragma once
#include <array>
#include "SFML/Graphics/Rect.hpp"
#include <vector>
#include <iostream>

struct QuadTree {
    virtual void f() {};

    unsigned int depth;
    sf::IntRect quadRect;
    std::array<QuadTree*, 4> children;


    virtual void insert(Agent* agent, int multiplier)
    {
        for (int i = 0; i < 4; i++)
        {
            if (children[i] != nullptr)
            {
                if (children[i]->quadRect.contains(sf::Vector2i(agent->getPosX() * multiplier, agent->getPosY() * multiplier)))
                {
                    children[i]->insert(agent, multiplier);
                    return;
                }
            }
        }
    }


    QuadTree(const sf::IntRect& rect, const unsigned int& depth)
        : depth(depth), quadRect(rect), children{ nullptr, nullptr, nullptr, nullptr } {}

    ~QuadTree() {
        for (QuadTree* child : children)
            delete[] child;
    }
};

struct QuadTreeLeaf : public QuadTree {

    // Josh: You'll need to change this so it can take multiple iterators. 
    // Later we'll add more objects to the BattlefieldVector which won't all be BattlefieldCells,
    // so better to try and open up the types of objects that the new list of iterators can point
    // at. Probably a "template" is a good way to accomplish that. 
    std::vector<BattlefieldCell>::iterator iter;

    void insert(Agent* agent, int multiplier) override
    {
        iter->Objects.push_back(*agent);
    }

    QuadTreeLeaf(const sf::IntRect& rect, const unsigned int& depth, std::vector<BattlefieldCell>::iterator& _iter)
        : QuadTree(rect, depth), iter(_iter) {}

private:
    sf::IntRect calculateChildRect(int index) const
    {
        int halfWidth = quadRect.width / 2;
        int halfHeight = quadRect.height / 2;
        int childLeft = quadRect.left + (index % 2) * halfWidth;
        int childTop = quadRect.top + (index / 2) * halfHeight;
        return sf::IntRect(childLeft, childTop, halfWidth, halfHeight);
    }
};