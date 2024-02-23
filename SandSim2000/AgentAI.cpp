#include "AgentAI.h"






AgentAI::~AgentAI()
{
}

bool AgentAI::AgentQueueAction(Action Action, bool ClearQueue)
{
	return false;
}

bool AgentAI::AgentMove(sf::Vector2i target)
{
	return false;
}

bool AgentAI::AgentShoot(sf::Vector2i target)
{
	return false;
}

bool AgentAI::AgentAssault()
{
	return false;
}

bool AgentAI::AgentGoToGround()
{
	return false;
}

bool AgentAI::AgentCollectResource(sf::Vector2i target)
{
	return false;
}

bool AgentAI::AgentConstruct(sf::Vector2i target)
{
	return false;
}

bool AgentAI::AgentPathFind(sf::Vector2i source, sf::Vector2i target)
{
	return false;
}

std::vector<sf::Vector2i> AgentAI::AStarPathFind(sf::Vector2i source, sf::Vector2i target)
{
	return std::vector<sf::Vector2i>();
}



