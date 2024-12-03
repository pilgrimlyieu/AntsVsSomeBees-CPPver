#ifndef SCARYTHROWER_H
#define SCARYTHROWER_H

#include "ThrowerAnt.h"

class ScaryThrower : public ThrowerAnt {
    void throwAt(Bee *target);

public:
    inline static const string name = "Scary"; //!< 类名
    static const int foodCost = 6;             //!< 食物消耗
};

#endif // SCARYTHROWER_H