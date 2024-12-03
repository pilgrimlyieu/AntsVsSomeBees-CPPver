#ifndef SCUBATHROWER_H
#define SCUBATHROWER_H

#include "ThrowerAnt.h"

class ScubaThrower : public ThrowerAnt {
public:
    inline static const string name = "Scuba"; //!< 类名
    static const int foodCost = 6;             //!< 食物消耗
    static const int isWaterProof = true;      //!< 是否抗水
};

#endif // SCUBATHROWER_H