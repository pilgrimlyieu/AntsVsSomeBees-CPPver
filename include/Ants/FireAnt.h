#ifndef FIREANT_H
#define FIREANT_H

#include "Ant.h"

class FireAnt : public Ant {
public:
    inline static const string name = "Fire"; //!< 类名
    int damage = 3;                           //!< 伤害
    int foodCost = 5;                         //!< 食物消耗

    void reduceHealth(int amount);
};

#endif // FIREANT_H