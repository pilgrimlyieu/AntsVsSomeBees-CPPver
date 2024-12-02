#ifndef SHORTTHROWER_H
#define SHORTTHROWER_H

#include "ThrowerAnt.h"

class ShortThrower : public ThrowerAnt {
public:
    string name = "ShortThrower";  // the name of the ShortThrower
    static const int foodCost = 2; // the food cost of the ShortThrower
    int maxRange = 3;              // the maximum range of the ShortThrower
};

#endif // SHORTTHROWER_H