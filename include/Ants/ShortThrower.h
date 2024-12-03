#ifndef SHORTTHROWER_H
#define SHORTTHROWER_H

#include "ThrowerAnt.h"

class ShortThrower : public ThrowerAnt {
public:
    inline static const string name = "ShortThrower"; //!< 类名
    static const int foodCost = 2;                    //!< 食物消耗
    int maxRange = 3;                                 //!< 最大射程
};

#endif // SHORTTHROWER_H