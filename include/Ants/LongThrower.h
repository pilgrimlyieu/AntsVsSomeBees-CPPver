#ifndef LONGTHROWER_H
#define LONGTHROWER_H

#include "ThrowerAnt.h"

class LongThrower : public ThrowerAnt {
public:
    inline static const string name = "LongThrower"; //!< 类名
    static const int foodCost = 2;                   //!< 食物消耗
    int minRange = 5;                                //!< 最小射程
};

#endif // LONGTHROWER_H