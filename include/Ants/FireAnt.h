#ifndef FIREANT_H
#define FIREANT_H

#include "Ant.h"

class FireAnt final : public Ant {
private:
    inline static const std::string name = "Fire"; //!< 类名
    double damage = 3.0;                           //!< 伤害
    static const int foodCost = 5;                 //!< 食物消耗

public:
    void reduceHealth(int amount) override final;
};

#endif // FIREANT_H