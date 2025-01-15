#ifndef SCUBATHROWER_H
#define SCUBATHROWER_H

#include "ThrowerAnt.hpp"

class ScubaThrower : public ThrowerAnt {
protected:
    struct scuba_thrower_properties : thrower_ant_properties {
        string name = "ScubaThrower";
        int foodCost = 6;
        bool isWaterProof = true;
    };

public:
    explicit ScubaThrower(double health, scuba_thrower_properties properties);

    explicit ScubaThrower(double health) : ScubaThrower(health, {}) {}

    explicit ScubaThrower() : ScubaThrower(1.0) {}
};

#endif // SCUBATHROWER_H