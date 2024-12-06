#ifndef SHORTTHROWER_H
#define SHORTTHROWER_H

#include "ThrowerAnt.h"

class ShortThrower final : public ThrowerAnt {
private:
    inline static const std::string name = "ShortThrower"; //!< 类名
    static const int foodCost = 2;                         //!< 食物消耗
    static const int maxRange = 3;                         //!< 最大射程
};

#endif // SHORTTHROWER_H