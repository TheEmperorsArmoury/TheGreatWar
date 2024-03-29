#pragma once
#include <cmath>
#include <set>

#include "GameState.h"
#include "BattlefieldMap.h"
#include "BattlefieldCell.h"
#include "Agent.h"
#include "InputStateManager.h"
#include "InputState.h"
#include "GridGenerator.h"
#include "Scenery.h"
#include "Tree.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "Scene.h"

class AgentManager
{
public:
	void onUpdate(
		const InputState& state, 
		std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
		GameStateManager& gameStateManager, 
		Camera& camera, 
		Scene& scene);
	void placeScenery(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery scenObject, GameStateManager& gameStateManager);
	void setX(int xPosition);
	void setY(int yPosition);

private:
	bool leftClick = false;
};