#include "Scene.h"

#define MAX_TILE_DEPTH 5
#define TILE_SIZE 100

Scene::Scene() {}

// Charlie Team: Please change the UpdateGameScene so it updates based on the zoom level condition
// found in the InputState. 0-2 zoom level is subterranean, 3-5 is tactical, don't worry about strategic for now.

void Scene::UpdateGameScene(Camera& cam, GameState& gameState) {
	GridGenerator gridGenerator;
	sf::IntRect viewbounds(0, 0, cam.window.getSize().x, cam.window.getSize().y);

	gameScene.clear();
	findViewportIterators(gameState.quadTree, cam, gridGenerator, viewbounds);
}

void Scene::findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds) {

	int screenX, screenY;
	sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(root->quadRect.getPosition().x / TILE_SIZE, root->quadRect.getPosition().y / TILE_SIZE));
	cam.WorldToScreen(isometricPosition.x + cam.window.getSize().x / 2, isometricPosition.y, screenX, screenY);

	int sizeX = root->quadRect.getSize().x * cam.scaleX;
	int sizeY = (root->quadRect.getSize().y / 2 + (TILE_SIZE / 2) * MAX_TILE_DEPTH) * cam.scaleY;

	sf::IntRect isometricNodeRect(screenX - sizeX / 2, screenY, sizeX, sizeY);

	if (!viewbounds.intersects(isometricNodeRect))
		return;

	if (typeid(*root) == typeid(QuadTreeLeaf)) {
		gameScene.insert(((QuadTreeLeaf*)root)->iter);
	} else {
		for (QuadTree* child : ((QuadTree*)root)->children)
			findViewportIterators(child, cam, gridGenerator, viewbounds);
	}
}