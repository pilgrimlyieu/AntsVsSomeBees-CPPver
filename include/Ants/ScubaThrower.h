#ifndef SCUBATHROWER_H
#define SCUBATHROWER_H

#include "ThrowerAnt.h"

struct scuba_thrower_properties : thrower_ant_properties {
    std::string name = "Scuba";
    int foodCost = 6;
    bool isWaterProof = true;
};

class ScubaThrower : public ThrowerAnt {
public:
    explicit ScubaThrower(double health = 1.0, scuba_thrower_properties properties = {});
};

#endif // SCUBATHROWER_H