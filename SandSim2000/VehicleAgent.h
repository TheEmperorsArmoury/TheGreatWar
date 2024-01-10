#pragma once
#include "Agent.h"

class VehicleAgent : public Agent {
private:
    std::string stance;
    int ammo;
public:
    VehicleAgent();
    ~VehicleAgent();

    void setAmmo(int agentAmmo);
    int getAmmo() const;
};