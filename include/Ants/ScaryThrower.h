#ifndef SCARYTHROWER_H
#define SCARYTHROWER_H

#include "ThrowerAnt.h"

class ScaryThrower : public ThrowerAnt {
    void throwAt(Bee *target);

public:
    string name = "Scary";         // the name of the Ant
    static const int foodCost = 6; // the food cost of the Ant
};

#endif // SCARYTHROWER_H