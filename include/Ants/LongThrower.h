#ifndef LONGTHROWER_H
#define LONGTHROWER_H

#include "ThrowerAnt.h"

class LongThrower final : public ThrowerAnt {
private:
    inline static const std::string name = "LongThrower"; //!< 类名
    static const int foodCost = 2;                        //!< 食物消耗
    static const int minRange = 5;                        //!< 最小射程
};

#endif // LONGTHROWER_H