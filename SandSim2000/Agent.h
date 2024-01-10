#pragma once
#include <string>
#include <utility>

class Agent {
private:
    std::string unit;
    std::pair<float, float> position;
    int health;
    int morale;

public:
    Agent();
    ~Agent();

    void setUnit(const std::string& agentUnit);
    void setPosition(const std::pair<float, float>& agentPosition);
    void setStance(const std::string& agentStance);
    void setHealth(int agentHealth);
    void setMorale(int agentMorale);
    void setPinned(bool agentPinned);
    void setAmmo(int agentAmmo);


    std::string getUnit() const;
    std::pair<float, float> getPosition() const;
    std::string getStance() const;
    int getHealth() const;
    int getMorale() const;
    bool isPinned() const;
    int getAmmo() const;
};
