#ifndef SLOWTHROWER_H
#define SLOWTHROWER_H

#include "ThrowerAnt.h"

class SlowThrower : public ThrowerAnt {
    void throwAt(Bee *target);

public:
    inline static const string name = "Slow"; //!< 类名
    static const int foodCost = 4;            //!< 食物消耗
};

#endif // SLOWTHROWER_H