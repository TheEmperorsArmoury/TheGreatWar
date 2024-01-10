#pragma once
#include "Agent.h"

class InfantryAndCavalryAgent : public Agent {
private:
    std::string stance;
    bool pinned;

public:
    InfantryAndCavalryAgent();
    ~InfantryAndCavalryAgent();

    void setPinned(bool agentPinned);
    bool isPinned() const;
};
