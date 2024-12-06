#ifndef SCARYTHROWER_H
#define SCARYTHROWER_H

#include "ThrowerAnt.h"

class ScaryThrower final : public ThrowerAnt {
private:
    inline static const std::string name = "Scary"; //!< 类名
    static const int foodCost = 6;                  //!< 食物消耗
    void throwAt(Bee *target);
};

#endif // SCARYTHROWER_H