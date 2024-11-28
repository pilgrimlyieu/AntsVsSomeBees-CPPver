#ifndef LONGTHROWER_H
#define LONGTHROWER_H

#include "ThrowerAnt.h"

class LongThrower : public ThrowerAnt {
  public:
    string name = "LongThrower";
    static const int foodCost = 2;
    int minRange = 5;
};

#endif // LONGTHROWER_H