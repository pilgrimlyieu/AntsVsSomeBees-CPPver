#ifndef SCUBATHROWER_H
#define SCUBATHROWER_H

#include "ThrowerAnt.h"

class ScubaThrower : public ThrowerAnt {
public:
    string name = "Scuba";                // the name of the Ant
    static const int foodCost = 6;        // the food cost of the Ant
    static const int isWaterProof = true; // the water proof ability of the Ant
};

#endif // SCUBATHROWER_H