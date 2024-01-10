#include "VehicleAgent.h"

VehicleAgent::VehicleAgent() : Agent(), ammo(0) {}

VehicleAgent::~VehicleAgent() {}

void VehicleAgent::setAmmo(int agentAmmo) {
    ammo = agentAmmo;
}

int VehicleAgent::getAmmo() const {
    return ammo;
}
