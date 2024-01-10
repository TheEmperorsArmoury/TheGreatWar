#include "InfantryAndCavalryAgent.h"

InfantryAndCavalryAgent::InfantryAndCavalryAgent() : Agent(), pinned(false) {}

InfantryAndCavalryAgent::~InfantryAndCavalryAgent() {}

void InfantryAndCavalryAgent::setPinned(bool agentPinned) {
    pinned = agentPinned;
}

bool InfantryAndCavalryAgent::isPinned() const {
    return pinned;
}
