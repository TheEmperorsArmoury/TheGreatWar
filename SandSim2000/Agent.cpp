#include "Agent.h"

Agent::Agent()
    : unit(""), position(0.0f, 0.0f), health(0), morale(0) {}

Agent::~Agent() {}

std::string Agent::getUnit() const {
    return unit;
}

void Agent::setUnit(const std::string& newUnit) {
    unit = newUnit;
}

std::pair<float, float> Agent::getPosition() const {
    return position;
}

void Agent::setPosition(const std::pair<float, float>& newPosition) {
    position = newPosition;
}

int Agent::getHealth() const {
    return health;
}

void Agent::setHealth(int newHealth) {
    health = newHealth;
}

int Agent::getMorale() const {
    return morale;
}

void Agent::setMorale(int newMorale) {
    morale = newMorale;
}
