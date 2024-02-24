#include "NavMesh.h"



NavMesh::NavMesh(sf::RenderWindow& window)
{
	m_window = &window;
	InitializeMesh();
}


NavMesh::~NavMesh()
{

}

bool NavMesh::InitializeMesh()
{
	// 2D array to initialize grid
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 20; y++)
		{

		}
	}
	
	return false;
}
