#ifndef SLOWTHROWER_H
#define SLOWTHROWER_H

#include "ThrowerAnt.h"

class SlowThrower : public ThrowerAnt {
    void throwAt(Bee *target);

public:
    string name = "Slow";          // the name of the Ant
    static const int foodCost = 4; // the food cost of the Ant
};

#endif // SLOWTHROWER_H