#ifndef SHORTTHROWER_H
#define SHORTTHROWER_H

#include "ThrowerAnt.h"

class ShortThrower : public ThrowerAnt {
  public:
    string name = "ShortThrower";
    static const int foodCost = 2;
    int maxRange = 3;
};

#endif // SHORTTHROWER_H