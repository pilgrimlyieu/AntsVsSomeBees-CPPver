#ifndef SLOWTHROWER_H
#define SLOWTHROWER_H

#include "ThrowerAnt.h"

class SlowThrower final : public ThrowerAnt {
private:
    inline static const std::string name = "Slow"; //!< 类名
    static const int foodCost = 4;                 //!< 食物消耗

    void throwAt(Bee *target);
};

#endif // SLOWTHROWER_H