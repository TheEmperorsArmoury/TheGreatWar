#pragma once
#include <array>
#include <memory>
#include <vector>
#include <list>

#include "SFML/Graphics/Rect.hpp"
//just for testing quadtree for now
#include "SFML/Graphics.hpp"

#include "MapInfo.h"

#define MAX_DEPTH 5

class QuadTree
{
public:
	QuadTree(sf::FloatRect size, unsigned int Depth);
	void resize(sf::FloatRect size);
	void clear();

	unsigned int size();
	void insert(MapInfo* item, sf::FloatRect itemSize); // Interts an object into the quad, or determines if it should go into a child quad

	std::list<MapInfo*> search(sf::FloatRect searchArea);
	void searchQuad(sf::FloatRect searchArea, std::list<MapInfo*>* coveredItems);

	void items(std::list<MapInfo*>* listItems);
	std::list<MapInfo*> items();
	sf::FloatRect getQuadRect() { return quadRect; }

	void debugDraw(sf::RenderWindow* window);

private:
	unsigned int depth = 0;

	//	Data on this quad
	sf::FloatRect quadRect;
	std::vector<MapInfo*> quadItems;

	//	The rect of the children quads
	std::array<sf::FloatRect, 4> childQuadRect{};
	//	A pointer to the children quads
	std::array<std::shared_ptr<QuadTree>, 4> childQuad;
};