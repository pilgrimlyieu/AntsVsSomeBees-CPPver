#ifndef LONGTHROWER_H
#define LONGTHROWER_H

#include "ThrowerAnt.h"

class LongThrower : public ThrowerAnt {
public:
    string name = "LongThrower";   // the name of the LongThrower
    static const int foodCost = 2; // the food cost of the LongThrower
    int minRange = 5;              // the minimum range of the LongThrower
};

#endif // LONGTHROWER_H