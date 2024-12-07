#ifndef SCUBATHROWER_H
#define SCUBATHROWER_H

#include "ThrowerAnt.h"

class ScubaThrower : public ThrowerAnt {
private:
    inline static const std::string name = "Scuba"; //!< 类名
    static const int foodCost = 6;                  //!< 食物消耗

public:
    static const bool isWaterProof = true; //!< 是否抗水
};

#endif // SCUBATHROWER_H