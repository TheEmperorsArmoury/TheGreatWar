#pragma once
#include <SFML/Graphics.hpp>



class NavMesh {
protected:
	// Defining the subdivisions of the navmesh
	const int m_MeshSize = 2000;
	const int m_CellSize = 100;



	sf::RectangleShape GridSquares[20][20];
	sf::RenderWindow* m_window;

public:
	NavMesh(sf::RenderWindow* window);
	~NavMesh();
	bool InitializeMesh();


};