#ifndef FIREANT_H
#define FIREANT_H

#include "Ant.h"

class FireAnt : public Ant {
private:
    inline static const std::string name = "Fire"; //!< 类名
    int damage = 3;                                //!< 伤害
    static const int foodCost = 5;                 //!< 食物消耗

public:
    void reduceHealth(int amount);
};

#endif // FIREANT_H