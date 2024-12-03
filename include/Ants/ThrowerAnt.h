#ifndef THROWERANT_H
#define THROWERANT_H

#include "Ant.h"

class ThrowerAnt : public Ant {
protected:
    Bee *nearestBee();
    void throwAt(Bee *target);

public:
    inline static const string name = "Thrower"; //!< 类名
    int damage = 1;                              //!< 伤害
    static const int foodCost = 3;               //!< 食物消耗
    int minRange = 0;                            //!< 最小射程
    int maxRange = INT_MAX;                      //!< 最大射程

    void action(GameState &gamestate);
};

#endif // THROWERANT_H