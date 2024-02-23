#include "Agent.h"
#include "InputStateManager.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <string>
#pragma once

class AgentAI {
protected:
	Agent controlledAgent;

	// For now the queue will store items of the action struct, this can be expanded to have more parameters if agentAi functions require
	struct Action {
		std::string ActionName;
		sf::Vector2i VectorParam;
	};

	// Action queue that the agent uses to execute tasks
	std::queue<Action> ActionQueue;
	
	// Testing purposes
	sf::RectangleShape ControlledRect;

	// AGENT ACTIONS
	// Military Descisions
	// Move along path may be unnecesary due to the action queue functionality
	//bool AgentMoveAlongPath(sf::Vector2i source, sf::Vector2i target);
	bool AgentMove(sf::Vector2i target);
	bool AgentShoot(sf::Vector2i target);
	bool AgentAssault();
	bool AgentGoToGround();
	// Economic Descisions - Require the objects of type building and resource to exist before implentation
	bool AgentCollectResource(sf::Vector2i target);
	bool AgentConstruct(sf::Vector2i target);

	// Utility actions
	bool AgentPathFind(sf::Vector2i, sf::Vector2i);
	std::vector<sf::Vector2i> AStarPathFind(sf::Vector2i, sf::Vector2i);

public:
	~AgentAI();
	
	bool AgentAIInit();

	bool AgentQueueAction(Action Action, bool ClearQueue);

};