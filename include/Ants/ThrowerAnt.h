#ifndef THROWERANT_H
#define THROWERANT_H

#include "Ant.h"

class ThrowerAnt : public Ant {
private:
    inline static const std::string name = "Thrower"; //!< 类名
    double damage = 1.0;                              //!< 伤害
    static const int foodCost = 3;                    //!< 食物消耗

protected:
    static const int minRange = 0;       //!< 最小射程
    static const int maxRange = INT_MAX; //!< 最大射程

    Bee *nearestBee();

    virtual void throwAt(Bee *target);

public:
    void action(GameState &gamestate) override;
};

#endif // THROWERANT_H